//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-instruction-node.h"

IRInstructionNode::IRInstructionNode(llvm::Instruction* irValue, IRType* type, IRNode* irNode) {
    _irValue = irValue;
    _type = type;
    _irNode = irNode;
}

llvm::Instruction* IRInstructionNode::getValue() {
    return _irValue;
}

IRType* IRInstructionNode::getIRType() {
    return _type;
}

IRNode* IRInstructionNode::getIRNode() {
    return _irNode;
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