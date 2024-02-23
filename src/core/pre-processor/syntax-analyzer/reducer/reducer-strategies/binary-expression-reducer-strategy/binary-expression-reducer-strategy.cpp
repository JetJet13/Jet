//
// Created by Johny Georges on 2024-02-19.
//

#include "binary-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

ASTNode* BinaryExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTBinaryExpressionNode(
            this->createExpressionNode(nodes[0]),
            (ASTBinaryOperatorNode*)nodes[1],
            this->createExpressionNode(nodes[2])
    );
}

ASTExpressionNode* BinaryExpressionReducerStrategy::createExpressionNode(ASTNode* node) {

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