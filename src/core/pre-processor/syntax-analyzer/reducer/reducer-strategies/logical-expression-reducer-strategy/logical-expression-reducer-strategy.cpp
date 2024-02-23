//
// Created by Johny Georges on 2024-02-20.
//

#include "logical-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

ASTNode* LogicalExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTLogicalExpressionNode(
            this->createExpressionNode(nodes[0]),
            (ASTLogicalOperatorNode*)nodes[1],
            this->createExpressionNode(nodes[2])
    );
}

ASTExpressionNode* LogicalExpressionReducerStrategy::createExpressionNode(ASTNode* node) {

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