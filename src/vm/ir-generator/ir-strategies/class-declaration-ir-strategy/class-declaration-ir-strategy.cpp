//
// Created by Johny Georges on 2024-12-09.
//

#include "class-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

IRClassDeclarationNode* ClassDeclarationIRStrategy::generate(ASTClassDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);

    for (auto method : *node->getBlock()->getMethods()) {
        this->declareMethod(method, irGenerator, scope, irContext, irClassType);
    }

    for (auto classConstructor : *node->getBlock()->getConstructors()) {
        this->declareConstructor(classConstructor, irGenerator, scope, irContext, irClassType);
    }

    auto irClassConstructors = std::vector<IRClassConstructorNode*>();
    for (auto constructor : *node->getBlock()->getConstructors()) {
        irClassConstructors.push_back(this->generate(constructor, irGenerator, scope, irContext, irClassType));
    }

    auto irPreConstructor = this->generatePreConstructor(node,  irGenerator, scope, irContext, irClassType);

    auto irClassMethods = std::vector<IRClassMethodNode*>();
    for (auto method : *node->getBlock()->getMethods()) {
        irClassMethods.push_back(this->generate(method,  irGenerator, scope, irContext, irClassType));
    }
    return new IRClassDeclarationNode(node, irClassType, irPreConstructor, irClassConstructors, irClassMethods);
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
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);
    auto classScopeParameterAllocation = irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType());
    preConstructorScope->insert(irClassType->getClassScopeParameterType().value()->getName(), classScopeParameterAllocation);
    functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(0), classScopeParameterAllocation));

    auto initialPropertyIRExpressions = new std::unordered_map<unsigned long, IRExpressionNode*>();
    for (auto property : *node->getBlock()->getProperties()) {
        if (property->getInitializer()) {
            auto propertyIndex = irClassType->getClassProperties()->getIndexForKey(property->getId());
            auto irExpression = irGenerator->generateFor(property->getInitializer().value(), preConstructorScope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
            irExpression->markAsAssigned();
            initialPropertyIRExpressions->insert(std::pair { propertyIndex, irExpression });
        }
    }
    return new IRClassPreConstructorNode(irFunction, classScopeParameterAllocation, initialPropertyIRExpressions, functionBlock, preConstructorScope);
}

IRClassConstructorNode* ClassDeclarationIRStrategy::generate(ASTClassConstructorDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto constructorScope = new IRLookupTable();
    constructorScope->inherit(scope);
    auto irFunction = irContext->getIRModule()->getModule()->getFunction(node->getId());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), constructorScope, irContext, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        auto scopeParameter = new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
        functionParameterList->addClassScopeParameter(scopeParameter);
        constructorScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    }

    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    for (unsigned long i = 0; i < irFunction->getFunctionType()->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
//        constructorScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
//        if (formalParameter->getArc()) {
//            constructorScope->insertArc(formalParameter->getParameterType()->getName(), formalParameter->getArc().value());
//        }
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, constructorScope, irContext));
    }

    return new IRClassConstructorNode(node, irFunction, functionParameterList, functionBlock, constructorScope);
}

IRClassMethodNode* ClassDeclarationIRStrategy::generate(ASTClassMethodDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto methodScope = new IRLookupTable();
    methodScope->inherit(scope);
    auto methodTypeNode = irClassType->getIRTypeForMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto irFunction = irContext->getIRModule()->getModule()->getFunction(node->getId());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), methodScope, irContext, irFunction);
    if (irClassType->getClassScopeParameterType()) {
        auto argument = new llvm::Argument(irClassType->getClassScopeParameterType().value()->getType(), irClassType->getClassScopeParameterType().value()->getName(), irFunction, 0);
        auto scopeParameter = new IRFunctionParameterNode(argument, irClassType->getClassScopeParameterType().value(), irGenerator->generateFunctionParameterAllocation(irClassType->getClassScopeParameterType().value()->getIRType()));
        functionParameterList->addClassScopeParameter(scopeParameter);
        methodScope->insert(scopeParameter->getParameterType()->getName(), scopeParameter->getAllocation());
    }
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    for (unsigned long i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
//        methodScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
//        if (formalParameter->getArc()) {
//            methodScope->insertArc(formalParameter->getParameterType()->getName(), formalParameter->getArc().value());
//        }
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, methodScope, irContext));
    }

    return new IRClassMethodNode(node, irFunction, functionParameterList, functionBlock, methodScope);
}

void ClassDeclarationIRStrategy::declareMethod(ASTClassMethodDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto methodTypeNode = irClassType->getIRTypeForMethod(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(methodTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irContext->getModule());
}

void ClassDeclarationIRStrategy::declareConstructor(ASTClassConstructorDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType) {
    auto constructorTypeNode = irClassType->getIRTypeForConstructor(node->getId()).value();
    auto functionType = llvm::cast<llvm::FunctionType>(constructorTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    llvm::Function::Create(functionType, linkage, 0, node->getId(), irContext->getModule());
}