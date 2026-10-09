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
// Created by Johny Georges on 2025-04-15.
//

#include "memcpy-ir-function.h"

std::string MemcpyIRFunction::getMemcpyIRFunctionName() {
    return "jet.memcpy";
}

void MemcpyIRFunction::generateMemcpyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto memcpy = irModuleNode->getModule()->get()->getOrInsertFunction("memcpy", llvm::FunctionType::get(pointerType, { pointerType, pointerType, intType }, false));
    auto functionType = llvm::FunctionType::get(pointerType, { pointerType, pointerType, intType }, false);

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MemcpyIRFunction::getMemcpyIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto destinationPointer = function->getArg(0);
    auto sourcePointer = function->getArg(1);
    auto copySize = function->getArg(2);
    functionBlock->getBuilder()->get()->CreateCall(memcpy, { destinationPointer, sourcePointer, copySize });
    functionBlock->getBuilder()->get()->CreateRet(destinationPointer);
}