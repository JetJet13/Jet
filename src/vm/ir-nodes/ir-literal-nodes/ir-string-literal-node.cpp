//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-string-literal-node.h"

IRStringLiteralNode::IRStringLiteralNode(ASTStringLiteralNode* astStringLiteralNode, llvm::ConstantArray* irValue) {
    _astNode = astStringLiteralNode;
    _irValue = irValue;
}

llvm::ConstantArray* IRStringLiteralNode::getIRValue() {
    return _irValue;
}

IRNodeType IRStringLiteralNode::getNodeType() {
    return IR_STRING_LITERAL_NODE;
}

std::string IRStringLiteralNode::toString() {
    return "IR_STRING_LITERAL_NODE";
}