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
// Created by Johny Georges on 2025-12-08.
//

#ifndef JETLANG_IR_TYPE_VALUE_INSTRUCTION_NODE_H
#define JETLANG_IR_TYPE_VALUE_INSTRUCTION_NODE_H

#include <llvm/IR/Instructions.h>

// forward declaration
class IRBlockNode;
class IRPointerType;

class IRTypeValueInstructionNode {
private:
    llvm::AllocaInst* _alloc;
    std::shared_ptr<IRPointerType> _irType;
    llvm::StoreInst* _initialValueStoreInstruction;
public:
    IRTypeValueInstructionNode(llvm::AllocaInst* alloc, std::shared_ptr<IRPointerType> irType, llvm::StoreInst* initialValueStoreInstruction);
    bool isInserted();
    llvm::AllocaInst* getValue();
    llvm::StoreInst* getInitialValueStoreInstruction();
    std::shared_ptr<IRTypeValueInstructionNode> clone();
    llvm::Type* getAllocatedType();
    llvm::MaybeAlign getAlignment();
    uint64_t getSizeInBytes();
    std::shared_ptr<IRPointerType> getIRType();
};

#endif //JETLANG_IR_TYPE_VALUE_INSTRUCTION_NODE_H
