//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-identifier-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-object-nodes/ast-object-access-source-node.h"
#include "../ast-function-nodes/ast-function-argument-node.h"
#include "../ast-tuple-nodes/ast-tuple-item-node.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(ASTIdentifierNode* identifierNode) {
    _identifierNode = identifierNode;
    _children.push_back(_identifierNode);
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