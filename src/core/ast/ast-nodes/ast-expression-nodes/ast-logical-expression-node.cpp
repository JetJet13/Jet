//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-logical-expression-node.h"

ASTLogicalExpressionNode::ASTLogicalExpressionNode(ASTExpressionNode* leftNode, ASTLogicalOperatorNode* logicalOperator, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _logicalOperator = logicalOperator;
    _rightNode = rightNode;
}

ASTNodeType ASTLogicalExpressionNode::getNodeType() {
    return AST_LOGICAL_EXPRESSION_NODE;
}

std::string ASTLogicalExpressionNode::toString() {
    return "LOGICAL_EXPRESSION";
}