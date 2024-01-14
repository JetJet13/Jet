//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-binary-expression-node.h"


ASTBinaryExpressionNode::ASTBinaryExpressionNode(Lexeme* binaryOperator) {
    _binaryOperator = binaryOperator;
}

void ASTBinaryExpressionNode::setLeftNode(ASTExpressionNode* astExpressionNode) {
    _leftNode = astExpressionNode;
}

void ASTBinaryExpressionNode::setRightNode(ASTExpressionNode* astExpressionNode) {
    _rightNode = astExpressionNode;
}