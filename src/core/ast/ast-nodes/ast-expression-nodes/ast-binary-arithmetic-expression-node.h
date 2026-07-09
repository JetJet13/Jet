//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BINARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_ARITHMETIC_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"

class ASTBinaryArithmeticExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _leftNode;
    std::shared_ptr<ASTExpressionNode> _rightNode;
    std::shared_ptr<ASTBinaryArithmeticOperatorNode> _binaryOperator;
    std::shared_ptr<TypeSignature> _leftTypeSignature = std::make_shared<UnknownTypeSignature>();
    std::shared_ptr<TypeSignature> _rightTypeSignature = std::make_shared<UnknownTypeSignature>();
public:
    ASTBinaryArithmeticExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTBinaryArithmeticOperatorNode> binaryOperator, std::shared_ptr<ASTExpressionNode> rightNode);
    std::shared_ptr<ASTExpressionNode> getLeftNode();
    std::shared_ptr<ASTExpressionNode> getRightNode();
    void setLeftTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    void setRightTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getLeftTypeSignature();
    std::shared_ptr<TypeSignature> getRightTypeSignature();
    std::shared_ptr<ASTBinaryArithmeticOperatorNode> getBinaryOperator();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_ARITHMETIC_EXPRESSION_NODE_H
