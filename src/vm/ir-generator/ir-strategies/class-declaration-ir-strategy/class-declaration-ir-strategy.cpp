//
// Created by Johny Georges on 2024-12-09.
//

#include "class-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRClassDeclarationNode> ClassDeclarationIRStrategy::generate(std::shared_ptr<ASTClassDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irClassType = irGenerator->generateTypeFor(node->getClassTypeSignature(), scope, irContext);

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

    auto irClassConstructors = std::vector<std::shared_ptr<IRClassConstructorNode>>();
    for (auto constructor : *node->getBlock()->getConstructors()) {
        irClassConstructors.push_back(this->generate(constructor, irGenerator, scope, irContext, irClassType));
    }

    auto irPreConstructor = this->generatePreConstructor(node,  irGenerator, scope, irContext, irClassType);

    auto irClassMethods = std::vector<std::shared_ptr<IRClassMethodNode>>();
    for (auto method : *node->getBlock()->getInstanceMethods()) {
        irClassMethods.push_back(this->generate(method,  irGenerator, scope, irContext, irClassType));
    }

    auto irClassStaticMethods = std::vector<std::shared_ptr<IRClassMethodNode>>();
    for (auto method : *node->getBlock()->getStaticMethods()) {
        irClassStaticMethods.push_back(this->generateStatic(method,  irGenerator, scope, irContext, irClassType));
    }

    auto irClassStaticProperties = std::vector<std::shared_ptr<IRClassStaticPropertyNode>>();
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

    return std::make_shared<IRClassDeclarationNode>(node, irValue, irClassType, irPreConstructor, irClassConstructors, irClassMethods, irClassStaticMethods, irClassStaticProperties);
}

std::optional<std::shared_ptr<IRClassPreConstructorNode>> ClassDeclarationIRStrategy::generatePreConstructor(std::shared_ptr<ASTClassDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto pointerType = irGenerator->generatePointerType();
    auto preConstructorScope = std::make_shared<IRLookupTable>();
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
    functionBlock->insert(std::make_shared<IRFunctionParameterDeclarationNode>(irFunction->getArg(0), classScopeParameterAllocation));

    auto initialPropertyIRExpressions = std::vector<std::pair<uint64_t, std::shared_ptr<IRExpressionNode>>>();
    auto initialPropertyConstants = std::vector<std::pair<uint64_t, llvm::Constant*>>();
    for (int i = 0; i < node->getBlock()->getInstanceProperties()->size(); ++i) {
        auto property = node->getBlock()->getInstanceProperties()->at(i);
        auto propertyIndex = irClassType->getClassProperties()->getStructIRType()->getIndexForKey(property->getId());
        if (property->getInitializer()) {
            auto irExpression = irGenerator->generateFor(property->getInitializer().value(), functionBlock->getScope(), irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
            irExpression->markAsAssigned();
            initialPropertyIRExpressions.push_back(std::pair { propertyIndex, irExpression });
        } else {
            auto irType = irGenerator->generateTypeFor(property->getPropertyTypeSignature()->getType(), scope, irContext);
            initialPropertyConstants.push_back(std::pair { propertyIndex, irGenerator->generateInitialValueForIRType(irType) });
        }
    }
    return std::make_shared<IRClassPreConstructorNode>(irFunction, classScopeParameterAllocation, initialPropertyIRExpressions, initialPropertyConstants, functionBlock);
}

std::shared_ptr<IRClassConstructorNode> ClassDeclarationIRStrategy::generate(std::shared_ptr<ASTClassConstructorDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto constructorScope = std::make_shared<IRLookupTable>();
    constructorScope->inherit(scope);
    auto irFunction = irContext->getIRModule()->getModule()->get()->getFunction(node->getId());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), constructorScope, irContext, irFunction);
    auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
    auto scopeParameter = std::make_shared<IRFunctionParameterNode>(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
    functionParameterList->addClassScopeParameter(scopeParameter);
    constructorScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());

    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, constructorScope);

    for (uint64_t i = 0; i < irFunction->getFunctionType()->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(std::make_shared<IRFunctionParameterDeclarationNode>(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irContext));
    }

    return std::make_shared<IRClassConstructorNode>(node, irFunction, functionParameterList, functionBlock);
}

std::shared_ptr<IRClassMethodNode> ClassDeclarationIRStrategy::generate(std::shared_ptr<ASTClassMethodDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto methodScope = std::make_shared<IRLookupTable>();
    methodScope->inherit(scope);
    auto methodId = FunctionIdGenerator::generateFor(node);
    auto methodTypeNode = irClassType->getIRTypeForMethod(methodId).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto irFunction = irContext->getIRModule()->getModule()->get()->getFunction(methodId);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), methodScope, irContext, irFunction);
    auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
    auto scopeParameter = std::make_shared<IRFunctionParameterNode>(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
    functionParameterList->addClassScopeParameter(scopeParameter);
    methodScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, methodScope);

    for (uint64_t i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(std::make_shared<IRFunctionParameterDeclarationNode>(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irContext));
    }

    auto globalVariableIRType = irGenerator->generateIRInvocableType();
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            globalVariableIRType->getType(),
            false,
            node->isExportable()
            ? llvm::GlobalValue::ExternalLinkage
            : llvm::GlobalValue::PrivateLinkage,
            irGenerator->generatePlaceholderValueForIRType(globalVariableIRType),
            methodId
    );
    auto irGlobalVariable = IRInstructionNodeFactory::create(
            globalVariable,
            irGenerator->generateIrPointerType(globalVariableIRType)
    );

    auto irClassMethodNode = std::make_shared<IRClassMethodNode>(node, irFunction, functionParameterList, functionBlock, irGlobalVariable);
    methodScope->insertGlobalVariable(methodId, irGlobalVariable);
    return irClassMethodNode;
}

std::shared_ptr<IRClassMethodNode> ClassDeclarationIRStrategy::generateStatic(std::shared_ptr<ASTClassMethodDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto methodScope = std::make_shared<IRLookupTable>();
    methodScope->inherit(scope);
    auto methodId = irClassType->addStaticSuffix(FunctionIdGenerator::generateFor(node));
    auto methodTypeNode = irClassType->getIRTypeForStaticMethod(methodId).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto irFunction = irContext->getIRModule()->getModule()->get()->getFunction(methodId);
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), methodScope, irContext, irFunction);
    auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
    auto scopeParameter = std::make_shared<IRFunctionParameterNode>(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
    functionParameterList->addClassScopeParameter(scopeParameter);
    methodScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, methodScope);

    for (uint64_t i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(std::make_shared<IRFunctionParameterDeclarationNode>(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irContext));
    }

    auto globalVariableIRType = irGenerator->generateIRInvocableType();
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            globalVariableIRType->getType(),
            false,
            node->isExportable()
            ? llvm::GlobalValue::ExternalLinkage
            : llvm::GlobalValue::PrivateLinkage,
            irGenerator->generatePlaceholderValueForIRType(globalVariableIRType),
            methodId
    );
    auto irGlobalVariable = IRInstructionNodeFactory::create(
            globalVariable,
            irGenerator->generateIrPointerType(globalVariableIRType)
    );

    auto irClassMethodNode = std::make_shared<IRClassMethodNode>(node, irFunction, functionParameterList, functionBlock, irGlobalVariable);
    methodScope->insertGlobalVariable(methodId, irGlobalVariable);
    return irClassMethodNode;
}

std::shared_ptr<IRClassStaticPropertyNode> ClassDeclarationIRStrategy::generateStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto irType = irClassType->getIRTypeForStaticProperty(node->getId());
    return std::make_shared<IRClassStaticPropertyNode>(
            node,
            irContext->getIRModule()->getModule()->get()->getNamedGlobal(irClassType->addStaticSuffix(node->getId())),
            irGenerator->generateFor(node->getInitializer().value(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP)),
            irType.value()
    );
}

void ClassDeclarationIRStrategy::declareMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto id = FunctionIdGenerator::generateFor(node);
    auto methodTypeNode = irClassType->getIRTypeForMethod(id).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = isExportable ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, id, irContext->getModule());
}

void ClassDeclarationIRStrategy::declareStaticMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto id = irClassType->addStaticSuffix(FunctionIdGenerator::generateFor(node));
    auto methodTypeNode = irClassType->getIRTypeForStaticMethod(id).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = isExportable ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, id, irContext->getModule());
}

void ClassDeclarationIRStrategy::declareConstructor(std::shared_ptr<ASTClassConstructorDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto constructorTypeNode = irClassType->getIRTypeForConstructor(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(constructorTypeNode->getType());
    auto linkage = isExportable ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irContext->getModule());
}

void ClassDeclarationIRStrategy::declareStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType) {
    auto irType = irClassType->getIRTypeForStaticProperty(node->getId());
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            irType.value()->getType(),
            false,
            isExportable
            ? llvm::GlobalValue::ExternalLinkage
            : llvm::GlobalValue::PrivateLinkage,
            irGenerator->generatePlaceholderValueForIRType(irType.value()),
            irClassType->addStaticSuffix(node->getId())
    );
    scope->insertGlobalVariable(irClassType->addStaticSuffix(node->getId()), IRInstructionNodeFactory::create(globalVariable));
}