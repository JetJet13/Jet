//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_LOGICAL_EXPRESSION_NODE_H
#define JETLANG_AST_LOGICAL_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"

class ASTLogicalExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    ASTLogicalOperatorNode* _logicalOperator;
public:
    ASTLogicalExpressionNode(ASTExpressionNode* leftNode, ASTLogicalOperatorNode* logicalOperator, ASTExpressionNode* rightNode);
    ASTExpressionNode* getLeftNode();
    ASTExpressionNode* getRightNode();
    ASTLogicalOperatorNode* getLogicalOperator();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_LOGICAL_EXPRESSION_NODE_H
