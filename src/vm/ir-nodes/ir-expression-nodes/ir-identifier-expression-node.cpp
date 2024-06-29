//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(ASTIdentifierExpressionNode* astIdentifierExpressionNode, llvm::Value* irValue) {
    _astNode = astIdentifierExpressionNode;
    _irValue = irValue;
}

llvm::Value* IRIdentifierExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRIdentifierExpressionNode::getNodeType() {
    return IR_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRIdentifierExpressionNode::toString() {
    return "IR_IDENTIFIER_EXPRESSION_NODE";
}