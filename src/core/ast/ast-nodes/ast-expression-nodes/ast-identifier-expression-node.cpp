//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-identifier-expression-node.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(ASTIdentifierNode* identifierNode) {
    _identifierNode = identifierNode;
}

ASTNodeType ASTIdentifierExpressionNode::getNodeType() {
    return AST_IDENTIFIER_EXPRESSION_NODE;
}