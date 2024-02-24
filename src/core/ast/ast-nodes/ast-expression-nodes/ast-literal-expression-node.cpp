//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-expression-node.h"

ASTLiteralExpressionNode::ASTLiteralExpressionNode(ASTLiteralNode* literalNode) {
    _literalNode = literalNode;
}

ASTNodeType ASTLiteralExpressionNode::getNodeType() {
    return AST_LITERAL_EXPRESSION_NODE;
}

std::string ASTLiteralExpressionNode::toString() {
    return "LITERAL_EXPRESSION";
}