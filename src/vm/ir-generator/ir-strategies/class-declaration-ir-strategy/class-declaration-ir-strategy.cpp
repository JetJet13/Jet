//
// Created by Johny Georges on 2024-12-09.
//

#include "class-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

IRClassDeclarationNode* ClassDeclarationIRStrategy::generate(ASTClassDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);

    for (auto method : *node->getBlock()->getInstanceMethods()) {
        this->declareMethod(method, node->isExportable(), irGenerator, scope, irContext, irClassType);
    }

    for (auto method : *node->getBlock()->getStaticMethods()) {
        this->declareStaticMethod(method, node->isExportable(), irGenerator, scope, irContext, irClassType);
    }

    for (auto classConstructor : *node->getBlock()->getConstructors()) {
        this->declareConstructor(classConstructor, node->isExportable(), irGenerator, scope, irContext, irClassType);
    }

    for (auto classStaticProperty : *node->getBlock()->getStaticProperties()) {
        this->declareStaticProperty(classStaticProperty, node->isExportable(), irGenerator, scope, irContext, irClassType);
    }

    auto irClassConstructors = std::vector<IRClassConstructorNode*>();
    for (auto constructor : *node->getBlock()->getConstructors()) {
        irClassConstructors.push_back(this->generate(constructor, irGenerator, scope, irContext, irClassType));
    }

    auto irPreConstructor = this->generatePreConstructor(node,  irGenerator, scope, irContext, irClassType);

    auto irClassMethods = std::vector<IRClassMethodNode*>();
    for (auto method : *node->getBlock()->getInstanceMethods()) {
        irClassMethods.push_back(this->generate(method,  irGenerator, scope, irContext, irClassType));
    }

    auto irClassStaticMethods = std::vector<IRClassMethodNode*>();
    for (auto method : *node->getBlock()->getStaticMethods()) {
        irClassStaticMethods.push_back(this->generateStatic(method,  irGenerator, scope, irContext, irClassType));
    }

    auto irClassStaticProperties = std::vector<IRClassStaticPropertyNode*>();
    for (auto staticClassProperty : *node->getBlock()->getStaticProperties()) {
        irClassStaticProperties.push_back(this->generateStaticProperty(staticClassProperty,  irGenerator, scope, irContext, irClassType));
    }

    auto globalVariableIrType = irGenerator->generateIrPointerType(irClassType);
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            globalVariableIrType->getType(),
            false,
            node->isExportable()
            ? llvm::GlobalValue::ExternalLinkage
            : llvm::GlobalValue::PrivateLinkage,
            irGenerator->generatePlaceholderValueForIRType(globalVariableIrType),
            node->getId()
    );
    auto irValue = IRInstructionNodeFactory::create(globalVariable, globalVariableIrType);
    scope->insertGlobalVariable(node->getId(), irValue);

    return new IRClassDeclarationNode(node, irValue, irClassType, irPreConstructor, irClassConstructors, irClassMethods, irClassStaticMethods, irClassStaticProperties);
}

std::optional<IRClassPreConstructorNode*> ClassDeclarationIRStrategy::generatePreConstructor(ASTClassDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    if (!irClassType->getClassScopeParameterType()) {
        return {};
    }
    auto pointerType = irGenerator->generatePointerType();
    auto preConstructorScope = new IRLookupTable();
    preConstructorScope->inherit(scope);
    auto functionType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(**irContext->getContext()),
            { pointerType },
            false
    );
    auto irFunction = llvm::cast<llvm::Function>(irContext->getModule()->getOrInsertFunction(irClassType->getPreConstructorName(), functionType).getCallee());
    if (node->isExportable()) {
        irFunction->setLinkage(llvm::GlobalValue::ExternalLinkage);
    }
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, preConstructorScope);
    auto classScopeParameterAllocation = irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType());
    functionBlock->getScope()->insert(irClassType->getClassScopeParameterType().value()->getName(), classScopeParameterAllocation);
    functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(0), classScopeParameterAllocation));

    auto initialPropertyIRExpressions = new std::vector<std::pair<unsigned long, IRExpressionNode*>>();
    auto initialPropertyConstants = new std::vector<std::pair<unsigned long, llvm::Constant*>>();
    for (int i = 0; i < node->getBlock()->getInstanceProperties()->size(); ++i) {
        auto property = node->getBlock()->getInstanceProperties()->at(i);
        auto propertyIndex = irClassType->getClassProperties()->getStructIRType()->getIndexForKey(property->getId());
        if (property->getInitializer()) {
            auto irExpression = irGenerator->generateFor(property->getInitializer().value(), functionBlock->getScope(), irContext, new IROperation(IR_OPERAND_VALUE_OP));
            irExpression->markAsAssigned();
            initialPropertyIRExpressions->push_back(std::pair { propertyIndex, irExpression });
        } else {
            auto irType = irGenerator->generateTypeFor(property->getTypeSignature()->getType(), scope, irContext);
            initialPropertyConstants->push_back(std::pair { propertyIndex, irGenerator->generateInitialValueForIRType(irType) });
        }
    }
    return new IRClassPreConstructorNode(irFunction, classScopeParameterAllocation, initialPropertyIRExpressions, initialPropertyConstants, functionBlock);
}

IRClassConstructorNode* ClassDeclarationIRStrategy::generate(ASTClassConstructorDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto constructorScope = new IRLookupTable();
    constructorScope->inherit(scope);
    auto irFunction = irContext->getIRModule()->getModule()->get()->getFunction(node->getId());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), constructorScope, irContext, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        auto scopeParameter = new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
        functionParameterList->addClassScopeParameter(scopeParameter);
        constructorScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    }

    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, constructorScope);

    for (unsigned long i = 0; i < irFunction->getFunctionType()->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irContext));
    }

    return new IRClassConstructorNode(node, irFunction, functionParameterList, functionBlock);
}

IRClassMethodNode* ClassDeclarationIRStrategy::generate(ASTClassMethodDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto methodScope = new IRLookupTable();
    methodScope->inherit(scope);
    auto methodTypeNode = irClassType->getIRTypeForMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto irFunction = irContext->getIRModule()->getModule()->get()->getFunction(node->getId());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), methodScope, irContext, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        auto scopeParameter = new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
        functionParameterList->addClassScopeParameter(scopeParameter);
        methodScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    }
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, methodScope);

    for (unsigned long i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irContext));
    }

    return new IRClassMethodNode(node, irFunction, functionParameterList, functionBlock);
}

IRClassMethodNode* ClassDeclarationIRStrategy::generateStatic(ASTClassMethodDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto methodScope = new IRLookupTable();
    methodScope->inherit(scope);
    auto methodTypeNode = irClassType->getIRTypeForStaticMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto irFunction = irContext->getIRModule()->getModule()->get()->getFunction(node->getId());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), methodScope, irContext, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        auto scopeParameter = new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
        functionParameterList->addClassScopeParameter(scopeParameter);
        methodScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    }
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, methodScope);

    for (unsigned long i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irContext));
    }

    return new IRClassMethodNode(node, irFunction, functionParameterList, functionBlock);
}

IRClassStaticPropertyNode* ClassDeclarationIRStrategy::generateStaticProperty(ASTClassPropertyDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto irType = irClassType->getIRTypeForStaticProperty(node->getId());
    return new IRClassStaticPropertyNode(
            node,
            irContext->getIRModule()->getModule()->get()->getNamedGlobal(node->getId()),
            irGenerator->generateFor(node->getInitializer().value(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irType.value()
    );
}

void ClassDeclarationIRStrategy::declareMethod(ASTClassMethodDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto methodTypeNode = irClassType->getIRTypeForMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = isExportable ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irContext->getModule());
}

void ClassDeclarationIRStrategy::declareStaticMethod(ASTClassMethodDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto methodTypeNode = irClassType->getIRTypeForStaticMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = isExportable ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irContext->getModule());
}

void ClassDeclarationIRStrategy::declareConstructor(ASTClassConstructorDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto constructorTypeNode = irClassType->getIRTypeForConstructor(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(constructorTypeNode->getType());
    auto linkage = isExportable ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irContext->getModule());
}

void ClassDeclarationIRStrategy::declareStaticProperty(ASTClassPropertyDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto irType = irClassType->getIRTypeForStaticProperty(node->getId());
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            irType.value()->getType(),
            node->isConstant(),
            isExportable
            ? llvm::GlobalValue::ExternalLinkage
            : llvm::GlobalValue::PrivateLinkage,
            irGenerator->generatePlaceholderValueForIRType(irType.value()),
            node->getId()
    );
    scope->insertGlobalVariable(node->getId(), IRInstructionNodeFactory::create(globalVariable));
}