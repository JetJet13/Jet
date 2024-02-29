//
// Created by Johny Georges on 2024-02-17.
//

#include "unary-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-plus-operator.h"
#include "../../../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-plus-operator-node.h"
#include "../../../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-minus-operator.h"
#include "../../../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-minus-operator-node.h"
#include "../../../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-bang-operator-node.h"

ASTNode* UnaryExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {

    if (this->endsWith(nodes, AST_INT_LITERAL_NODE) ||
        this->endsWith(nodes, AST_FLOAT_LITERAL_NODE) ||
        this->endsWith(nodes, AST_STRING_LITERAL_NODE) ||
        this->endsWith(nodes, AST_CHAR_LITERAL_NODE) ||
        this->endsWith(nodes, AST_BOOLEAN_LITERAL_NODE)
        ) {
        return new ASTUnaryExpressionNode(
                this->createOperatorNode(nodes[0]),
                new ASTLiteralExpressionNode((ASTLiteralNode*)nodes[1])
        );
    }


    if (this->endsWith(nodes, AST_IDENTIFIER_NODE)) {
        return new ASTUnaryExpressionNode(
                this->createOperatorNode(nodes[0]),
                new ASTIdentifierExpressionNode((ASTIdentifierNode*)nodes[1])
        );
    }

    return new ASTUnaryExpressionNode(
            this->createOperatorNode(nodes[0]),
            (ASTExpressionNode*)nodes[1]
    );


}

ASTUnaryOperatorNode* UnaryExpressionReducerStrategy::createOperatorNode(ASTNode* node) {
    if (node->is(AST_PLUS_OPERATOR_NODE)) {
        auto plusOperatorNode = (ASTPlusOperatorNode*)node;
        return new ASTUnaryPlusOperatorNode(plusOperatorNode->getOperator());
    } else if (node->is(AST_MINUS_OPERATOR_NODE)) {
        auto minusOperatorNode = (ASTMinusOperatorNode*)node;
        return new ASTUnaryMinusOperatorNode(minusOperatorNode->getOperator());
    }
    return (ASTBangOperatorNode*)node;
}