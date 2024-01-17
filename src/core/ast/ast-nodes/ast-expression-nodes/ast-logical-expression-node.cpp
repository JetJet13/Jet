//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-logical-expression-node.h"

ASTLogicalExpressionNode::ASTLogicalExpressionNode(Lexeme* logicalOperator) {
    _logicalOperator = logicalOperator;
}

void ASTLogicalExpressionNode::setLeftNode(ASTExpressionNode* astExpressionNode) {
    _leftNode = astExpressionNode;
}

void ASTLogicalExpressionNode::setRightNode(ASTExpressionNode* astExpressionNode) {
    _rightNode = astExpressionNode;
}

ASTNodeType ASTLogicalExpressionNode::getNodeType() {
    return AST_LOGICAL_EXPRESSION_NODE;
}