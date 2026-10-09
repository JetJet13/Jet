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
// Created by Johny Georges on 2025-03-24.
//

#ifndef JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H
#define JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-injector.h"

class InstructionIRInjectorHelper {
public:
    static llvm::Value* inject(std::shared_ptr<IRTypeValueInstructionNode> irTypeValueInstructionNode, std::shared_ptr<IRBlockNode> irBlock, std::string name = "");
    static llvm::Value* inject(std::shared_ptr<IRInstructionNode> irInstruction, std::shared_ptr<IRBlockNode> irBlock, std::string name = "");
    static llvm::Value* injectLoad(std::shared_ptr<IRInstructionNode> irInstruction, std::shared_ptr<IRBlockNode> irBlock, std::string name = "");
    static llvm::Value* injectLoad(std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourcePointer, std::shared_ptr<IRBlockNode> irBlock, std::string name = "");
    static llvm::LoadInst* injectLoad(llvm::Type* type, llvm::Value* source, std::shared_ptr<IRBlockNode> irBlock, std::optional<std::shared_ptr<IRType>> irType = {}, std::string name = "");
    static llvm::StoreInst* injectStore(llvm::Value* value, llvm::Value* source, std::shared_ptr<IRBlockNode> irBlock, std::optional<std::shared_ptr<IRType>> irType = {});
};

#endif //JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H
