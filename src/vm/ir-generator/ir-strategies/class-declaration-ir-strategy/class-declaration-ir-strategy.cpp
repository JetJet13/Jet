//
// Created by Johny Georges on 2024-12-09.
//

#include "class-declaration-ir-strategy.h"
#include "../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

IRClassDeclarationNode* ClassDeclarationIRStrategy::generate(ASTClassDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irClassType = irGenerator->generateTypeFor(node->getTypeSignature(), scope);
    scope->insert(node->getId(), irClassType);

    for (auto method : *node->getBlock()->getMethods()) {
        this->declareMethod(method, context, irGenerator, scope, irModule, irClassType);
    }

    auto irClassConstructors = std::vector<IRClassConstructorNode*>();
    for (auto constructor : *node->getBlock()->getConstructors()) {
        irClassConstructors.push_back(this->generate(constructor, context, irGenerator, scope, irModule, irClassType));
    }

    this->generatePreConstructor(node, context, irGenerator, scope, irModule, irClassType);

    auto irClassMethods = std::vector<IRClassMethodNode*>();
    for (auto method : *node->getBlock()->getMethods()) {
        irClassMethods.push_back(this->generate(method, context, irGenerator, scope, irModule, irClassType));
    }
    return new IRClassDeclarationNode(node, irClassType, irClassConstructors, irClassMethods);
}

void ClassDeclarationIRStrategy::generatePreConstructor(ASTClassDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType) {
    if (!irClassType->getClassScopeParameterType()) {
        return;
    }
    auto preConstructorScope = new IRLookupTable();
    preConstructorScope->inherit(scope);
    auto functionType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(**context),
            { irClassType->getClassScopeParameterType().value()->getType() },
            false
    );
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, 0, irClassType->getPreConstructorName(), irModule->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    auto classScopeParameterAllocation = IRInstructionNodeFactory::create(irClassType->getClassScopeParameterType().value()->getIRType());
    preConstructorScope->insert(irClassType->getClassScopeParameterType().value()->getName(), classScopeParameterAllocation);
    irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(0), classScopeParameterAllocation), irModule, preConstructorScope);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    for (auto property : *node->getBlock()->getProperties()) {
        if (property->getInitializer()) {
            auto irExpression = irGenerator->generateFor(property->getInitializer().value(), preConstructorScope, irModule, IR_OPERAND_OP);
            auto irExpressionValue = irGenerator->getInjector()->inject(functionBlock, irExpression, IR_OPERAND_OP, irModule, preConstructorScope);
            auto propertyIndex = irGenerator->generateIntConstant(irClassType->getClassProperties()->getIndexForKey(property->getId()));
            auto pointerToProperty = llvm::GetElementPtrInst::CreateInBounds(classScopeParameterAllocation->getIRType()->getSourceType()->getSourceType()->getType(), classScopeParameterAllocation->getValue(), { zeroIndex, propertyIndex });
            functionBlock->getBuilder()->get()->Insert(pointerToProperty);
            functionBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointerToProperty);
        }
    }
    functionBlock->getBuilder()->get()->CreateRet(irGenerator->generateIntConstant(0));
}

IRClassConstructorNode* ClassDeclarationIRStrategy::generate(ASTClassConstructorDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType) {
    auto constructorScope = new IRLookupTable();
    constructorScope->inherit(scope);
    auto constructorTypeNode = irClassType->getIRTypeForConstructor(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(constructorTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, 0, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), constructorScope, irModule, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        functionParameterList->addScopeParameter(new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value()));
    }
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    for (int i = 0; i < functionType->getNumParams(); ++i) {
        auto parameter = functionType->params()[i];
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto irParamType = formalParameter->getParameterType()->getIRType();
        auto functionParameterAllocation = new IRInstructionNode(
                new llvm::AllocaInst(
                        parameter,
                        AddressSpaceGenerator::generate(irParamType),
                        nullptr,
                        DataAlignmentGenerator::generate(irParamType)
                ), irGenerator->generateIrPointerType(irParamType));
        constructorScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation), irModule, constructorScope);
    }

    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTDeclarationNode*) statement, constructorScope, irModule), irModule, constructorScope);
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTStatementNode*)statement, constructorScope, irModule), irModule, constructorScope);
        }
    }
    irGenerator->getInjector()->injectVoidReturnType(functionBlock);
    return new IRClassConstructorNode(irFunction);
}

IRClassMethodNode* ClassDeclarationIRStrategy::generate(ASTClassMethodDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType) {
    auto methodScope = new IRLookupTable();
    methodScope->inherit(scope);
    auto methodTypeNode = irClassType->getIRTypeForMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, 0, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), methodScope, irModule, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        functionParameterList->addScopeParameter(new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value()));
    }
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    for (int i = 0; i < functionType->getNumParams(); ++i) {
        auto parameter = functionType->params()[i];
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto irParamType = formalParameter->getParameterType()->getIRType();
        auto functionParameterAllocation = new IRInstructionNode(
                new llvm::AllocaInst(
                        parameter,
                        AddressSpaceGenerator::generate(irParamType),
                        nullptr,
                        DataAlignmentGenerator::generate(irParamType)
                ), irGenerator->generateIrPointerType(irParamType));
        methodScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation), irModule, methodScope);
    }

    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTDeclarationNode*) statement, methodScope, irModule), irModule, methodScope);
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTStatementNode*)statement, methodScope, irModule), irModule, methodScope);
        }
    }

    if (!node->getReturnType()) {
        irGenerator->getInjector()->injectVoidReturnType(functionBlock);
    }
    return new IRClassMethodNode(irFunction);
}

void ClassDeclarationIRStrategy::declareMethod(ASTClassMethodDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType) {
    auto methodTypeNode = irClassType->getIRTypeForMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irModule->getModule());
}