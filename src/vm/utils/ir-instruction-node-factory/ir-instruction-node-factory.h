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
// Created by Johny Georges on 2024-07-27.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
#define JETLANG_IR_INSTRUCTION_NODE_FACTORY_H

#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../ir-type/ir-array-pointer-type.h"

class IRInstructionNodeFactory {
public:
    static std::shared_ptr<IRInstructionNode> create(llvm::GlobalVariable* globalVariable);
    static std::shared_ptr<IRInstructionNode> create(llvm::GlobalVariable* globalVariable, std::shared_ptr<IRPointerType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> childAllocationMap);
    static std::shared_ptr<IRInstructionNode> create(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceInstructionNode);

    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRInstructionNode> otherInstructionNode);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRInstructionNode> otherInstructionNode, std::shared_ptr<IRInstructionNode> sourceInstructionNode);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> childAllocationMap);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType, llvm::Value* numElements);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType, std::shared_ptr<IRInstructionNode> sourceAllocation);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRType> irType, std::shared_ptr<IRInstructionNode> sourceAllocation);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRType> irType);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType, std::string name);
    static std::shared_ptr<IRInstructionNode> create(std::shared_ptr<IRPointerType> irType, std::string name, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation);
};

#endif //JETLANG_IR_INSTRUCTION_NODE_FACTORY_H
