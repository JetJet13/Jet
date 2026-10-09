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

#include "malloc-size-ir-function.h"

std::string MallocSizeIRFunction::getMallocSizeIRFunctionName() {
    return "jet.malloc.size";
}

void MallocSizeIRFunction::generateMallocSizeFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto functionType = llvm::FunctionType::get(irGenerator->generateIntType(), {irGenerator->generateIntType(), irGenerator->generateIntType() }, false);


    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MallocSizeIRFunction::getMallocSizeIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto numElements = function->getArg(0);
    auto elementSize = function->getArg(1);
    auto mallocSize = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, numElements, elementSize);

    functionBlock->getBuilder()->get()->CreateRet(mallocSize);
}