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
// Created by Johny Georges on 2025-02-22.
//

#include "malloc-free-ir-function.h"

std::string MallocFreeIRFunction::getMallocFreeIRFunctionName() {
    return "jet.malloc.free";
}

void MallocFreeIRFunction::generateMallocFreeFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { irGenerator->generatePointerType() }, false);
    auto free = irModuleNode->getModule()->get()->getOrInsertFunction("free", functionType);

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocFreeIRFunction::getMallocFreeIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    functionBlock->getBuilder()->get()->CreateCall(free, { function->getArg(0) });
    if (irModuleNode->isDebugMode()) {
        auto freeCounter = irModuleNode->getModule()->get()->getGlobalVariable("DEBUG_FREE_COUNTER");
        auto currentFreeCounter = functionBlock->getBuilder()->get()->CreateLoad(intType, freeCounter);
        auto newFreeCounter = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, currentFreeCounter, irGenerator->generateIntConstant(1));
        functionBlock->getBuilder()->get()->CreateStore(newFreeCounter, freeCounter);
    }
    functionBlock->addVoidReturn();
}