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
    std::shared_ptr<TypeSignature> _leftTypeSignature = std::make_shared<UnknownTypeSignature>();
    std::shared_ptr<TypeSignature> _rightTypeSignature = std::make_shared<UnknownTypeSignature>();
public:
    ASTBinaryComparatorExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperator, std::shared_ptr<ASTExpressionNode> rightNode);
    std::shared_ptr<ASTExpressionNode> getLeftNode();
    std::shared_ptr<ASTExpressionNode> getRightNode();
    void setLeftTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    void setRightTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getLeftTypeSignature();
    std::shared_ptr<TypeSignature> getRightTypeSignature();
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
