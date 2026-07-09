//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_LOGICAL_EXPRESSION_NODE_H
#define JETLANG_AST_LOGICAL_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"

class ASTLogicalExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _leftNode;
    std::shared_ptr<ASTExpressionNode> _rightNode;
    std::shared_ptr<ASTLogicalOperatorNode> _logicalOperator;
public:
    ASTLogicalExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTLogicalOperatorNode> logicalOperator, std::shared_ptr<ASTExpressionNode> rightNode);
    std::shared_ptr<ASTExpressionNode> getLeftNode();
    std::shared_ptr<ASTExpressionNode> getRightNode();
    std::shared_ptr<ASTLogicalOperatorNode> getLogicalOperator();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_LOGICAL_EXPRESSION_NODE_H
