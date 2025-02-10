//
// Created by Johny Georges on 2024-07-25.
//

#include "ir-global-variable-node.h"

IRGlobalVariableNode::IRGlobalVariableNode(llvm::GlobalVariable* irValue, IRPointerType* type, std::optional<llvm::GlobalVariable*> source) {
    _irValue = irValue;
    _type = type;
    _source = source;
}

llvm::GlobalVariable* IRGlobalVariableNode::getValue() {
    return _irValue;
}

llvm::GlobalVariable* IRGlobalVariableNode::getSource() {
    return _source.value_or(_irValue);
}

IRPointerType* IRGlobalVariableNode::getIRType() {
    return _type;
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