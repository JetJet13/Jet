//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"

IRInstructionNode::IRInstructionNode(llvm::AllocaInst* irValue, IRType* type) {
    _irValue = irValue;
    _type = type;
}

llvm::AllocaInst* IRInstructionNode::getValue() {
    return _irValue;
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