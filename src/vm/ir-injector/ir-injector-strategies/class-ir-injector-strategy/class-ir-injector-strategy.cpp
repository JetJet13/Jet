// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-12-27.
//

#include "class-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-invocable-type.h"

void ClassIRInjectorStrategy::inject(std::shared_ptr<IRClassDeclarationNode> irClassDeclarationNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
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

void ClassIRInjectorStrategy::injectPreConstructor(std::shared_ptr<IRClassPreConstructorNode> irClassPreConstructorNode, std::shared_ptr<IRClassType> irClassType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto preConstructorBlock = irClassPreConstructorNode->getBlock();
    auto preConstructorScope = irClassPreConstructorNode->getBlock()->getScope();
    irInjector->inject(irBlock, preConstructorBlock, irModule);
    auto classScopeParameterAllocation = irClassPreConstructorNode->getClassScopeParameter();
    auto classInstanceIrType = std::dynamic_pointer_cast<IRStructRefType>(irClassType->getClassScopeParameterType().value()->getIRType()->getSourceType());
    auto pointerType = irClassPreConstructorNode->getClassScopeParameter()->getIRType()->getType();

    auto classInstancePropertiesAlloc = InstructionIRInjectorHelper::injectLoad(classScopeParameterAllocation->getAllocatedType(), classScopeParameterAllocation->getValue(), preConstructorBlock);
    auto pointerToClassInstancePropertiesAlloc = preConstructorBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getType(), classInstancePropertiesAlloc, classInstanceIrType->getStructIndex());
    auto classInstancePropertiesStructAlloc = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToClassInstancePropertiesAlloc, preConstructorBlock);
    DebugIRInjectorHelper::injectLog(preConstructorBlock, irClassType->getId(), irInjector, irModule);
    for (auto keyValue : *irClassPreConstructorNode->getExpressions()) {
            auto pointerToProperty = preConstructorBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getStructIRType()->getType(), classInstancePropertiesStructAlloc, keyValue.first);
            auto irExpressionValue = irInjector->inject(preConstructorBlock, keyValue.second, std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, preConstructorScope);
            InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToProperty, preConstructorBlock, classInstanceIrType->getStructIRType()->getIRTypeByIndex(keyValue.first));
    }

    for (auto keyValue : *irClassPreConstructorNode->getInitializers()) {
        auto pointerToProperty = preConstructorBlock->getBuilder()->get()->CreateStructGEP(classInstanceIrType->getStructIRType()->getType(), classInstancePropertiesStructAlloc, keyValue.first);
        InstructionIRInjectorHelper::injectStore(keyValue.second, pointerToProperty, preConstructorBlock, classInstanceIrType->getStructIRType()->getIRTypeByIndex(keyValue.first));
    }
    irClassPreConstructorNode->getBlock()->addVoidReturn();
}

void ClassIRInjectorStrategy::injectConstructor(std::shared_ptr<IRClassConstructorNode> irClassConstructorNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irInjector->inject(irBlock, irClassConstructorNode->getBlock(), irModule);

    irClassConstructorNode->getBlock()->addVoidReturn();

    FreeIRInjectorHelper::freeFunctionBlockNodes(irClassConstructorNode->getBlock(), irInjector, irModule, irClassConstructorNode->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irClassConstructorNode->getBlock(), irClassConstructorNode->getParameters(), irInjector, irModule, irClassConstructorNode->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irClassConstructorNode->getBlock(), irClassConstructorNode->getNode()->getId(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irClassConstructorNode->getBlock(), irClassConstructorNode->getNode()->getId(), irInjector, irModule);
}

void ClassIRInjectorStrategy::injectMethod(std::shared_ptr<IRClassMethodNode> irClassMethodNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irInjector->inject(irBlock, irClassMethodNode->getBlock(), irModule);

    if (!irClassMethodNode->getNode()->getReturnType()) {
        irClassMethodNode->getBlock()->addVoidReturn();
    }

    auto irType = std::dynamic_pointer_cast<IRInvocableType>(irClassMethodNode->getGlobalVariable()->getIRType()->getSourceType());
    auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irClassMethodNode->getGlobalVariable()->getValue(), irType->getFunctionIndex());
    InstructionIRInjectorHelper::injectStore(irClassMethodNode->getFunction(), functionPointer, irBlock, irType);
    auto refCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irClassMethodNode->getGlobalVariable()->getValue(), irType->getFunctionRefCounterIndex());
    auto refCounterAlloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getRefCounterSizeInBytes()),
            }
    );
    auto refCounterValue = irBlock->getBuilder()->get()->getInt64(1);
    InstructionIRInjectorHelper::injectStore(refCounterValue, refCounterAlloc, irBlock);
    InstructionIRInjectorHelper::injectStore(refCounterAlloc, refCounterPointer, irBlock);

    auto isPerpetualPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irClassMethodNode->getGlobalVariable()->getValue(), irType->getIsPerpetualIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getTrue(), isPerpetualPointer, irBlock);

    FreeIRInjectorHelper::freeFunctionBlockNodes(irClassMethodNode->getBlock(), irInjector, irModule, irClassMethodNode->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irClassMethodNode->getBlock(), irClassMethodNode->getParameters(), irInjector, irModule, irClassMethodNode->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irClassMethodNode->getBlock(), irClassMethodNode->getNode()->getId(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irClassMethodNode->getBlock(), irClassMethodNode->getNode()->getId(), irInjector, irModule);
}

void ClassIRInjectorStrategy::injectStaticProperty(std::shared_ptr<IRClassStaticPropertyNode> irClassStaticPropertyNode, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto valueIrOperation = std::make_shared<IROperation>(IR_OPERAND_VALUE_OP);
    auto initialValue = irInjector->inject(irBlock, irClassStaticPropertyNode->getInitialIRValue(), valueIrOperation, irModule, scope);
    InstructionIRInjectorHelper::injectStore(initialValue, irClassStaticPropertyNode->getGlobalVariable(), irBlock, irClassStaticPropertyNode->getIRType());
    // we need to increment the ref count for static properties that require arc because they are similar to global variables,
    // which means they need the extra ref increment on initialization to prevent them from being freed after first use
    if (irClassStaticPropertyNode->getIRType()->requiresArc()) {
        irClassStaticPropertyNode->getIRType()->isInvocableType()
        ? irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irClassStaticPropertyNode->getGlobalVariable() })
        : irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irClassStaticPropertyNode->getGlobalVariable() });
    }
}