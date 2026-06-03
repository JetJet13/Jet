//
// Created by Johny Georges on 2025-12-27.
//

#include "class-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ClassIRInjectorStrategy::inject(IRClassDeclarationNode* irClassDeclarationNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irClassDeclarationNode->getPreConstructor()) {
        this->injectPreConstructor(irClassDeclarationNode->getPreConstructor().value(), irClassDeclarationNode->getIRType(), irBlock, irInjector, irModule, scope);
    }
    for (auto irConstructor : *irClassDeclarationNode->getConstructors()) {
        this->injectConstructor(irConstructor, irBlock, irInjector, irModule, scope);
    }

    for (auto irMethod : *irClassDeclarationNode->getMethods()) {
        this->injectMethod(irMethod, irBlock, irInjector, irModule, scope);
    }

    for (auto irStaticMethod : *irClassDeclarationNode->getStaticMethods()) {
        this->injectMethod(irStaticMethod, irBlock, irInjector, irModule, scope);
    }

    for (auto irStaticProperty : *irClassDeclarationNode->getStaticProperties()) {
        this->injectStaticProperty(irStaticProperty, irBlock, irInjector, irModule, scope);
    }
}

void ClassIRInjectorStrategy::injectPreConstructor(IRClassPreConstructorNode* irClassPreConstructorNode, IRClassType* irClassType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto preConstructorBlock = irClassPreConstructorNode->getBlock();
    auto preConstructorScope = irClassPreConstructorNode->getBlock()->getScope();
    irInjector->inject(irBlock, preConstructorBlock, irModule);
    auto classScopeParameterAllocation = irClassPreConstructorNode->getClassScopeParameter();
    auto classInstanceIrType = (IRStructRefType*)irClassType->getClassScopeParameterType().value()->getIRType()->getSourceType();
    auto pointerType = irClassPreConstructorNode->getClassScopeParameter()->getIRType()->getType();

    auto classInstancePropertiesAlloc = InstructionIRInjectorHelper::injectLoad(classScopeParameterAllocation->getAllocatedType(), classScopeParameterAllocation->getValue(), preConstructorBlock);
    auto pointerToClassInstancePropertiesAlloc = preConstructorBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getType(), classInstancePropertiesAlloc, classInstanceIrType->getStructIndex());
    auto classInstancePropertiesStructAlloc = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToClassInstancePropertiesAlloc, preConstructorBlock);
    DebugIRInjectorHelper::injectLog(preConstructorBlock, irClassType->getId(), irInjector, irModule);
    for (auto keyValue : *irClassPreConstructorNode->getExpressions()) {
            auto pointerToProperty = preConstructorBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getStructIRType()->getType(), classInstancePropertiesStructAlloc, keyValue.first);
            auto irExpressionValue = irInjector->inject(preConstructorBlock, keyValue.second, new IROperation(IR_COPY_ASSIGNMENT_OP), irModule, preConstructorScope);
            InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToProperty, preConstructorBlock);
    }

    for (auto keyValue : *irClassPreConstructorNode->getInitializers()) {
        auto pointerToProperty = preConstructorBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getStructIRType()->getType(), classInstancePropertiesStructAlloc, keyValue.first);
        InstructionIRInjectorHelper::injectStore(keyValue.second, pointerToProperty, preConstructorBlock);
    }
    irClassPreConstructorNode->getBlock()->addVoidReturn();
}

void ClassIRInjectorStrategy::injectConstructor(IRClassConstructorNode* irClassConstructorNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irClassConstructorNode->getBlock(), irModule);

    irClassConstructorNode->getBlock()->addVoidReturn();

    FreeIRInjectorHelper::freeFunctionBlockNodes(irClassConstructorNode->getBlock(), irInjector, irModule, irClassConstructorNode->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irClassConstructorNode->getBlock(), irClassConstructorNode->getParameters(), irInjector, irModule, irClassConstructorNode->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irClassConstructorNode->getBlock(), irClassConstructorNode->getNode()->getId(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irClassConstructorNode->getBlock(), irClassConstructorNode->getNode()->getId(), irInjector, irModule);
}

void ClassIRInjectorStrategy::injectMethod(IRClassMethodNode* irClassMethodNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irClassMethodNode->getBlock(), irModule);

    if (!irClassMethodNode->getNode()->getReturnType()) {
        irClassMethodNode->getBlock()->addVoidReturn();
    }

    FreeIRInjectorHelper::freeFunctionBlockNodes(irClassMethodNode->getBlock(), irInjector, irModule, irClassMethodNode->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irClassMethodNode->getBlock(), irClassMethodNode->getParameters(), irInjector, irModule, irClassMethodNode->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irClassMethodNode->getBlock(), irClassMethodNode->getNode()->getId(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irClassMethodNode->getBlock(), irClassMethodNode->getNode()->getId(), irInjector, irModule);
}

void ClassIRInjectorStrategy::injectStaticProperty(IRClassStaticPropertyNode* irClassStaticPropertyNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto initialValue = irInjector->inject(irBlock, irClassStaticPropertyNode->getInitialIRValue(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    InstructionIRInjectorHelper::injectStore(initialValue, irClassStaticPropertyNode->getGlobalVariable(), irBlock, irClassStaticPropertyNode->getIRType());
    // we need to increment the ref count for static properties that require arc because they are similar to global variables,
    // which means they need the extra ref increment on initialization to prevent them from being freed after first use
    if (irClassStaticPropertyNode->getIRType()->requiresArc()) {
        irClassStaticPropertyNode->getIRType()->isInvocableType()
        ? irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irClassStaticPropertyNode->getGlobalVariable() })
        : irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irClassStaticPropertyNode->getGlobalVariable() });
    }
}