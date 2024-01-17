//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_LOGICAL_EXPRESSION_NODE_H
#define JETLANG_AST_LOGICAL_EXPRESSION_NODE_H

#include "ast-expression-node.h"

class ASTLogicalExpressionNode : public ASTNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    Lexeme* _logicalOperator;
public:
    ASTLogicalExpressionNode(Lexeme* logicalOperator);
    void setLeftNode(ASTExpressionNode* astExpressionNode);
    void setRightNode(ASTExpressionNode* astExpressionNode);
    ASTNodeType getNodeType() override;
};


#endif //JETLANG_AST_LOGICAL_EXPRESSION_NODE_H
