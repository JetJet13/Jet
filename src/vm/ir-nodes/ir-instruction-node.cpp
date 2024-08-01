//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"

#include <utility>

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type, IRInstructionNode* sourceAllocation) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = sourceAllocation;
    _childSourceAllocations = std::vector<IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type, IRInstructionNode* sourceAllocation, std::vector<IRInstructionNode*> childSourceAllocations) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = sourceAllocation;
    _childSourceAllocations = std::move(childSourceAllocations);
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = {};
    _childSourceAllocations = std::vector<IRInstructionNode*>();
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type, std::vector<IRInstructionNode*> childSourceAllocations) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = {};
    _childSourceAllocations = std::move(childSourceAllocations);
}

llvm::AllocaInst* IRInstructionNode::getValue() {
    return _irValue;
}

IRInstructionNode* IRInstructionNode::getSourceAllocation() {
    if (_sourceAllocation) {
        return _sourceAllocation.value();
    }
    return this;
}

IRInstructionNode* IRInstructionNode::getSourceAllocationAtIndex(unsigned long index) {
    return _childSourceAllocations[index];
}

IRType* IRInstructionNode::getIRType() {
    return _type;
}

IRNodeType IRInstructionNode::getNodeType() {
    return IR_ALLOCATION_NODE;
}

std::string IRInstructionNode::toString() {
    return "IR_ALLOCATION_NODE";
}

void IRInstructionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}