//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BINARY_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-symbol-node.h"
#include "../ast-operator-nodes/ast-binary-operator-node.h"

class ASTBinaryExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    ASTBinaryOperatorNode* _binaryOperator;
public:
    ASTBinaryExpressionNode(ASTBinaryOperatorNode* binaryOperator);
    void setLeftNode(ASTExpressionNode* astExpressionNode);
    void setRightNode(ASTExpressionNode* astExpressionNode);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_BINARY_EXPRESSION_NODE_H
