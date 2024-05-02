//
// Created by Johny Georges on 2024-02-17.
//

#include "reducer-strategy.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"

ReducerStrategy::ReducerStrategy() {
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
    } else if (node->is(AST_CLASS_PROPERTY_ACCESS_NODE)) {
        return new ASTClassPropertyAccessExpressionNode((ASTClassPropertyAccessNode*)node);
    } else if (node->is(AST_THIS_NODE)) {
        return new ASTThisExpressionNode((ASTThisNode*)node);
    }

    return (ASTExpressionNode*)node;
}