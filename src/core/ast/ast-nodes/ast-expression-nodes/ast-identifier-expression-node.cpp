//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-identifier-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(ASTIdentifierNode* identifierNode) {
    _identifierNode = identifierNode;
    _children.push_back(_identifierNode);
}

ASTIdentifierNode* ASTIdentifierExpressionNode::getIdentifierNode() {
    return _identifierNode;
}

Position* ASTIdentifierExpressionNode::getStartPosition() {
    return _identifierNode->getStartPosition();
}

Position* ASTIdentifierExpressionNode::getEndPosition() {
    return _identifierNode->getEndPosition();
}

ASTNodeType ASTIdentifierExpressionNode::getNodeType() {
    return AST_IDENTIFIER_EXPRESSION_NODE;
}

std::string ASTIdentifierExpressionNode::toString() {
    return "IDENTIFIER_EXPRESSION";
}

bool ASTIdentifierExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierExpressionNode*)other;
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTIdentifierExpressionNode::print() {
    Logger::log(this->toString(), "-", _identifierNode->toString());
}

std::string ASTIdentifierExpressionNode::toSourceCode() {
    return _identifierNode->toSourceCode();
}