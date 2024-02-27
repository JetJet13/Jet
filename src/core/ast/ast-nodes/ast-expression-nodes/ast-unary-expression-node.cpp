//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-unary-expression-node.h"


ASTUnaryExpressionNode::ASTUnaryExpressionNode(ASTUnaryOperatorNode* unaryOperator, ASTExpressionNode* astExpressionNode) {
    _unaryOperator = unaryOperator;
    _expression = astExpressionNode;
}

ASTExpressionNode* ASTUnaryExpressionNode::getExpressionNode() {
    return _expression;
}

ASTUnaryOperatorNode* ASTUnaryExpressionNode::getUnaryOperatorNode() {
    return _unaryOperator;
}

ASTNodeType ASTUnaryExpressionNode::getNodeType() {
    return AST_UNARY_EXPRESSION_NODE;
}

std::string ASTUnaryExpressionNode::toString() {
    return "UNARY_EXPRESSION";
}

bool ASTUnaryExpressionNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUnaryExpressionNode*)other;
    return this->getUnaryOperatorNode()->isEqual(otherNode->getUnaryOperatorNode()) &&
    this->getExpressionNode()->isEqual(otherNode->getExpressionNode());
}