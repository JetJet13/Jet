//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-global-variable-node.h"

IRGlobalVariableNode::IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type, IRInstructionNode* sourceAllocation) {
    _irValue = irValue;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

llvm::GlobalVariable* IRGlobalVariableNode::getValue() {
    return _irValue;
}

IRPointerType* IRGlobalVariableNode::getIRType() {
    return _type;
}

IRInstructionNode* IRGlobalVariableNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRNodeType IRGlobalVariableNode::getNodeType() {
    return IR_GLOBAL_VARIABLE_NODE;
}

std::string IRGlobalVariableNode::toString() {
    return "IR_GLOBAL_VARIABLE_NODE";
}

void IRGlobalVariableNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}