//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_UNARY_EXPRESSION_NODE_H
#define JETLANG_AST_UNARY_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"

class ASTUnaryExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _argument;
    ASTUnaryOperatorNode* _unaryOperator;
public:
    ASTUnaryExpressionNode(ASTUnaryOperatorNode* unaryOperator, ASTExpressionNode* astExpressionNode);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_UNARY_EXPRESSION_NODE_H
