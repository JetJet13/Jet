//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-string-literal-node.h"

IRStringLiteralNode::IRStringLiteralNode(ASTStringLiteralNode* astNode, llvm::Constant* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Constant* IRStringLiteralNode::getConstantIRValue() {
    return _irValue;
}

llvm::Constant* IRStringLiteralNode::getIRValue() {
    return _irValue;
}

IRNodeType IRStringLiteralNode::getNodeType() {
    return IR_STRING_LITERAL_NODE;
}

std::string IRStringLiteralNode::toString() {
    return "IR_STRING_LITERAL_NODE";
}