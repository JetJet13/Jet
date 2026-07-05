//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-string-literal-node.h"

IRStringLiteralNode::IRStringLiteralNode(std::shared_ptr<ASTStringLiteralNode> astNode, llvm::Constant* irValue, std::shared_ptr<IRArrayType> type) {
    _astNode = astNode;
    _irValue = irValue;
    _type = type;
}

llvm::Constant* IRStringLiteralNode::getConstantIRValue() {
    return _irValue;
}

std::shared_ptr<IRArrayType> IRStringLiteralNode::getIRArrayType() {
    return _type;
}

std::shared_ptr<IRType> IRStringLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRStringLiteralNode::getNodeType() {
    return IR_STRING_LITERAL_NODE;
}

std::string IRStringLiteralNode::toString() {
    return "IR_STRING_LITERAL_NODE";
}

void IRStringLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}