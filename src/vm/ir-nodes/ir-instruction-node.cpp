//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type, IRInstructionNode* sourceAllocation) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = {};
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