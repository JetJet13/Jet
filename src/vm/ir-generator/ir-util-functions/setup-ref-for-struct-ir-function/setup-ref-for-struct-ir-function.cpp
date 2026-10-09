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
// Created by Johny Georges on 2025-12-19.
//

#include "setup-ref-for-struct-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SetupRefForStructIRFunction::getSetupRefForStructIRFunctionName() {
    return "jet.setup.ref.for.struct";
}

void SetupRefForStructIRFunction::generateSetupRefForStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(pointerType);
    auto structRefType = irGenerator->generateIRStructRefType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupRefForStructIRFunction::getSetupRefForStructIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getSharedValueIndex());
    InstructionIRInjectorHelper::injectStore(function->getArg(1), pointerToRefValuePointer, functionBlock);

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getRefCounterIndex());
    auto pointerToStructRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getCounterIndex());
    auto structRefCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToStructRefCounterPointer, functionBlock);
    InstructionIRInjectorHelper::injectStore(structRefCounterPointer, pointerToRefCounterPointer, functionBlock);

    functionBlock->addVoidReturn();
}