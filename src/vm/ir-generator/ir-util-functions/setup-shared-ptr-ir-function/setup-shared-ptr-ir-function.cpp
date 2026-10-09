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
// Created by Johny Georges on 2025-05-16.
//

#include "setup-shared-ptr-ir-function.h"

std::string SetupSharedPtrIRFunction::getSetupSharedPtrIRFunctionName() {
    return "jet.setup.shared.ptr";
}

void SetupSharedPtrIRFunction::generateSetupSharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           SetupSharedPtrIRFunction::getSetupSharedPtrIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getSharedValueIndex());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(1), pointerToNewRefValuePointer);

    auto intType = IRType(irGenerator->generateIntType());

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0),
                                                                                          sharedPtrType->getRefCounterIndex());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(2), pointerToRefCounterPointer);
    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getIncrementRefCountFunction(), { function->getArg(0) });
    functionBlock->addVoidReturn();
}