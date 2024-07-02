//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-char-literal-node.h"

IRCharLiteralNode::IRCharLiteralNode(ASTCharLiteralNode* astNode, llvm::ConstantInt* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Constant* IRCharLiteralNode::getConstantIRValue() {
    return _irValue;
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