//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BINARY_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_EXPRESSION_NODE_H

#include "ast-expression-node.h"

class ASTBinaryExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    Lexeme* _binaryOperator;
public:
    ASTBinaryExpressionNode(Lexeme* binaryOperator);
    void setLeftNode(ASTExpressionNode* astExpressionNode);
    void setRightNode(ASTExpressionNode* astExpressionNode);
};

#endif //JETLANG_AST_BINARY_EXPRESSION_NODE_H
