//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-logical-expression-node.h"

ASTLogicalExpressionNode::ASTLogicalExpressionNode(ASTExpressionNode* leftNode, ASTLogicalOperatorNode* logicalOperator, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _logicalOperator = logicalOperator;
    _rightNode = rightNode;
}

ASTExpressionNode* ASTLogicalExpressionNode::getLeftNode() {
    return _leftNode;
}

ASTExpressionNode* ASTLogicalExpressionNode::getRightNode() {
    return _rightNode;
}

ASTLogicalOperatorNode* ASTLogicalExpressionNode::getLogicalOperator() {
    return _logicalOperator;
}

ASTNodeType ASTLogicalExpressionNode::getNodeType() {
    return AST_LOGICAL_EXPRESSION_NODE;
}

std::string ASTLogicalExpressionNode::toString() {
    return "LOGICAL_EXPRESSION";
}

bool ASTLogicalExpressionNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLogicalExpressionNode*)other;
    return this->getLogicalOperator()->isEqual(otherNode->getLogicalOperator()) &&
           this->getLeftNode()->isEqual(otherNode->getLeftNode()) &&
           this->getRightNode()->isEqual(otherNode->getRightNode());
}