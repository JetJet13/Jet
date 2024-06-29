//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-char-literal-node.h"

IRCharLiteralNode::IRCharLiteralNode(ASTCharLiteralNode* astCharLiteralNode, llvm::ConstantInt* irValue) {
    _astNode = astCharLiteralNode;
    _irValue = irValue;
}

llvm::ConstantInt* IRCharLiteralNode::getIRValue() {
    return _irValue;
}

IRNodeType IRCharLiteralNode::getNodeType() {
    return IR_CHAR_LITERAL_NODE;
}

std::string IRCharLiteralNode::toString() {
    return "IR_CHAR_LITERAL_NODE";
}