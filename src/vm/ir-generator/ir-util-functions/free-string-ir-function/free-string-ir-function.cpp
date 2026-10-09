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
// Created by Johny Georges on 2025-05-01.
//

#include "free-string-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string FreeStringIRFunction::getFreeStringIRFunctionName() {
    return "jet.free.string";
}

void FreeStringIRFunction::declareFreeStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeStringIRFunction::getFreeStringIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeStringIRFunction::generateFreeStringFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto charType = std::make_shared<IRType>(irGenerator->generateCharType());
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);

    auto function = irModuleNode->getFreeStringFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto sourceAllocationPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedSourceAllocation = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), sourceAllocationPointer);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { loadedSourceAllocation }
    );
    functionBlock->addVoidReturn();
}