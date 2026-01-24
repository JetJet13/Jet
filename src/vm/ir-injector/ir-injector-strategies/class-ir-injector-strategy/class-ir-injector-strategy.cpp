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
}

void ClassIRInjectorStrategy::injectPreConstructor(IRClassPreConstructorNode* irClassPreConstructorNode, IRClassType* irClassType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto preConstructorBlock = irClassPreConstructorNode->getBlock();
    auto preConstructorScope = irClassPreConstructorNode->getScope();
    irInjector->inject(irBlock, preConstructorBlock, irModule, preConstructorScope);
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
    irClassPreConstructorNode->getBlock()->addVoidReturn();
}

void ClassIRInjectorStrategy::injectConstructor(IRClassConstructorNode* irClassConstructorNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irClassConstructorNode->getBlock(), irModule, irClassConstructorNode->getScope());

    irClassConstructorNode->getBlock()->addVoidReturn();

    FreeIRInjectorHelper::freeFunctionBlockNodes(irClassConstructorNode->getBlock(), irInjector, irModule, irClassConstructorNode->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irClassConstructorNode->getBlock(), irClassConstructorNode->getParameters(), irInjector, irModule, irClassConstructorNode->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irClassConstructorNode->getBlock(), irClassConstructorNode->getNode()->getId(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irClassConstructorNode->getBlock(), irClassConstructorNode->getNode()->getId(), irInjector, irModule);
}

void ClassIRInjectorStrategy::injectMethod(IRClassMethodNode* irClassMethodNode, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irClassMethodNode->getBlock(), irModule, irClassMethodNode->getScope());

    if (!irClassMethodNode->getNode()->getReturnType()) {
        irClassMethodNode->getBlock()->addVoidReturn();
    }

    FreeIRInjectorHelper::freeFunctionBlockNodes(irClassMethodNode->getBlock(), irInjector, irModule, irClassMethodNode->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irClassMethodNode->getBlock(), irClassMethodNode->getParameters(), irInjector, irModule, irClassMethodNode->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irClassMethodNode->getBlock(), irClassMethodNode->getNode()->getId(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irClassMethodNode->getBlock(), irClassMethodNode->getNode()->getId(), irInjector, irModule);
}