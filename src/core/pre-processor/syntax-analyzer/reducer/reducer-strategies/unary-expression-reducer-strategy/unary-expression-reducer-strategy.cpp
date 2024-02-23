//
// Created by Johny Georges on 2024-02-17.
//

#include "unary-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"

ASTNode* UnaryExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {


    if (this->endsWith(nodes, AST_INT_LITERAL_NODE) ||
        this->endsWith(nodes, AST_FLOAT_LITERAL_NODE) ||
        this->endsWith(nodes, AST_STRING_LITERAL_NODE) ||
        this->endsWith(nodes, AST_CHAR_LITERAL_NODE) ||
        this->endsWith(nodes, AST_BOOLEAN_LITERAL_NODE)
        ) {
        return new ASTUnaryExpressionNode(
                (ASTUnaryOperatorNode*)nodes[0],
                new ASTLiteralExpressionNode((ASTLiteralNode*)nodes[1])
        );
    }


    if (this->endsWith(nodes, AST_IDENTIFIER_NODE)) {
        return new ASTUnaryExpressionNode(
                (ASTUnaryOperatorNode*)nodes[0],
                new ASTIdentifierExpressionNode((ASTIdentifierNode*)nodes[1])
        );
    }

    return new ASTUnaryExpressionNode(
            (ASTUnaryOperatorNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );


}