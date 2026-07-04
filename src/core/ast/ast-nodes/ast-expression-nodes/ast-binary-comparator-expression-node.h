//
// Created by Johny Georges on 2026-03-02.
//

#ifndef JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"

class ASTBinaryComparatorExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _leftNode;
    std::shared_ptr<ASTExpressionNode> _rightNode;
    std::shared_ptr<ASTBinaryComparatorOperatorNode> _binaryOperator;
    TypeSignature* _leftTypeSignature = new UnknownTypeSignature();
    TypeSignature* _rightTypeSignature = new UnknownTypeSignature();
public:
    ASTBinaryComparatorExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperator, std::shared_ptr<ASTExpressionNode> rightNode);
    std::shared_ptr<ASTExpressionNode> getLeftNode();
    std::shared_ptr<ASTExpressionNode> getRightNode();
    void setLeftTypeSignature(TypeSignature* typeSignature);
    void setRightTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getLeftTypeSignature();
    TypeSignature* getRightTypeSignature();
    std::shared_ptr<ASTBinaryComparatorOperatorNode> getBinaryOperator();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H
