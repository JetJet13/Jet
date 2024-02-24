//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-binary-expression-node.h"


ASTBinaryExpressionNode::ASTBinaryExpressionNode(ASTExpressionNode* leftNode, ASTBinaryOperatorNode* binaryOperator, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _binaryOperator = binaryOperator;
    _rightNode = rightNode;
}

ASTNodeType ASTBinaryExpressionNode::getNodeType() {
    return AST_BINARY_EXPRESSION_NODE;
}

std::string ASTBinaryExpressionNode::toString() {
    return "BINARY_EXPRESSION";
}