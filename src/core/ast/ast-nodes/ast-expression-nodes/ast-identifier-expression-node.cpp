//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-identifier-expression-node.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(ASTIdentifierNode* identifierNode) {
    _identifierNode = identifierNode;
}

ASTIdentifierNode* ASTIdentifierExpressionNode::getIdentifierNode() {
    return _identifierNode;
}

ASTNodeType ASTIdentifierExpressionNode::getNodeType() {
    return AST_IDENTIFIER_EXPRESSION_NODE;
}

std::string ASTIdentifierExpressionNode::toString() {
    return "IDENTIFIER_EXPRESSION";
}

bool ASTIdentifierExpressionNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierExpressionNode*)other;
    return this->getIdentifierNode()->isEqual(otherNode->getIdentifierNode());
}