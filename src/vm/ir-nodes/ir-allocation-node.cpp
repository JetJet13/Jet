//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-allocation-node.h"

IRAllocationNode::IRAllocationNode(llvm::AllocaInst* irValue, IRType* type) {
    _irValue = irValue;
    _type = type;
}

llvm::AllocaInst* IRAllocationNode::getValue() {
    return _irValue;
}

IRType* IRAllocationNode::getIRType() {
    return _type;
}

IRNodeType IRAllocationNode::getNodeType() {
    return IR_ALLOCATION_NODE;
}

std::string IRAllocationNode::toString() {
    return "IR_ALLOCATION_NODE";
}

void IRAllocationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}