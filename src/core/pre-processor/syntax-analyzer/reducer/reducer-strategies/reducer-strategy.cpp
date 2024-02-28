//
// Created by Johny Georges on 2024-02-17.
//

#include "reducer-strategy.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

bool ReducerStrategy::startsWith(std::vector<ASTNode*> nodes, ASTNodeType astNodeType) {
    if (nodes.empty()) {
        return false;
    }
    return nodes[0]->is(astNodeType);
}

bool ReducerStrategy::endsWith(std::vector<ASTNode*> nodes, ASTNodeType astNodeType) {
    if (nodes.empty()) {
        return false;
    }
    return nodes[nodes.size() - 1]->is(astNodeType);
}

ASTExpressionNode* ReducerStrategy::createExpressionNode(ASTNode* node) {

    if (node->is(AST_INT_LITERAL_NODE) ||
        node->is(AST_FLOAT_LITERAL_NODE) ||
        node->is(AST_STRING_LITERAL_NODE) ||
        node->is(AST_CHAR_LITERAL_NODE) ||
        node->is(AST_BOOLEAN_LITERAL_NODE)) {
        return new ASTLiteralExpressionNode((ASTLiteralNode*)node);
    } else if (node->is(AST_IDENTIFIER_NODE)) {
        return new ASTIdentifierExpressionNode((ASTIdentifierNode*)node);
    } else {
        return (ASTExpressionNode*)node;
    }
}