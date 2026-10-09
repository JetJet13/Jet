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
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_IR_INSTRUCTION_NODE_H
#define JETLANG_IR_INSTRUCTION_NODE_H

#include <unordered_map>
#include "ir-node.h"
#include "../ir-type/ir-type.h"
#include "../ir-type/ir-pointer-type.h"

// forward declaration
class IRBlockNode;

class IRInstructionNode : public IRNode {
protected:
    llvm::Value* _irValue;
    std::vector<llvm::Value*> _ancestorValues;
    std::vector<llvm::Value*> _descendentValues;
    std::optional<std::shared_ptr<IRInstructionNode>> _parentAllocation;
    std::vector<std::shared_ptr<IRInstructionNode>> _childAllocations;
    std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> _childAllocationMap;
    std::shared_ptr<IRPointerType> _irType;
    bool _isGlobal = false;
public:
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::shared_ptr<IRInstructionNode> parentAllocation, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::optional<std::shared_ptr<IRInstructionNode>> parentAllocation);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::optional<std::shared_ptr<IRInstructionNode>> parentAllocation);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::vector<std::shared_ptr<IRInstructionNode>> childAllocations);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::vector<llvm::Value*> descendentValues);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::vector<llvm::Value*> ancestorValues, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> childAllocationMap);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> childAllocationMap);
    IRInstructionNode(llvm::Value* irValue, std::shared_ptr<IRPointerType> irType);
    bool isGlobal();
    void markAsGlobal();
    bool isInserted();
    bool isValueGlobalVariable();
    llvm::Value* getValue();
    llvm::Type* getAllocatedType();
    std::vector<llvm::Value*>* getAncestorValues();
    std::vector<llvm::Value*>* getDescendentValues();
    std::optional<std::shared_ptr<IRInstructionNode>> getParentAllocation();
    std::vector<std::shared_ptr<IRInstructionNode>>* getChildAllocations();
    void insertAncestorValue(llvm::Value* ancestorValue);
    void insertDescendentValue(llvm::Value* descendentValue);
    bool hasChildAllocationMap();
    std::shared_ptr<IRInstructionNode> getChildAllocationForKey(std::string key);
    void setParentAllocation(std::optional<std::shared_ptr<IRInstructionNode>> parentAllocation);
    llvm::MaybeAlign getAlignment();
    uint64_t getSizeInBytes();
    std::shared_ptr<IRPointerType> getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void printChildAllocations();
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INSTRUCTION_NODE_H
