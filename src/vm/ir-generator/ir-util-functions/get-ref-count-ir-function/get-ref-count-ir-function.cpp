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
// Created by Johny Georges on 2025-12-12.
//

#include "get-ref-count-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string GetRefCountIRFunction::getGetRefCountIRFunctionName() {
    return "jet.get.ref.count";
}

void GetRefCountIRFunction::generateGetRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto irSharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(intType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, GetRefCountIRFunction::getGetRefCountIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefCountPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), function->getArg(0), irSharedPtrType->getRefCounterIndex());
    auto loadedRefCountPointer = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToRefCountPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        InstructionIRInjectorHelper::injectLoad(intType, loadedRefCountPointer, functionBlock)
    );

}