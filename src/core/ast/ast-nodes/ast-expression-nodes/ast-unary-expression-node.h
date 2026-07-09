//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_UNARY_EXPRESSION_NODE_H
#define JETLANG_AST_UNARY_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"

class ASTUnaryExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _expression;
    std::shared_ptr<ASTUnaryOperatorNode> _unaryOperator;
public:
    ASTUnaryExpressionNode(std::shared_ptr<ASTUnaryOperatorNode> unaryOperator, std::shared_ptr<ASTExpressionNode> astExpressionNode);
    std::shared_ptr<ASTExpressionNode> getExpressionNode();
    std::shared_ptr<ASTUnaryOperatorNode> getUnaryOperatorNode();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_UNARY_EXPRESSION_NODE_H
