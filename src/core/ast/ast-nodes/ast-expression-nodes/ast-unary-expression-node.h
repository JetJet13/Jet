//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_UNARY_EXPRESSION_NODE_H
#define JETLANG_AST_UNARY_EXPRESSION_NODE_H

#include "ast-expression-node.h"

class ASTUnaryExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _argument;
    Lexeme* _unaryOperator;
public:
    ASTUnaryExpressionNode(Lexeme* unaryOperator);
    void setArgument(ASTExpressionNode* astExpressionNode);
};

#endif //JETLANG_AST_UNARY_EXPRESSION_NODE_H
