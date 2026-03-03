//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BINARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_ARITHMETIC_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"

class ASTBinaryArithmeticExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    ASTBinaryArithmeticOperatorNode* _binaryOperator;
    TypeSignature* _leftTypeSignature = new UnknownTypeSignature();
    TypeSignature* _rightTypeSignature = new UnknownTypeSignature();
public:
    ASTBinaryArithmeticExpressionNode(ASTExpressionNode* leftNode, ASTBinaryArithmeticOperatorNode* binaryOperator, ASTExpressionNode* rightNode);
    ASTExpressionNode* getLeftNode();
    ASTExpressionNode* getRightNode();
    void setLeftTypeSignature(TypeSignature* typeSignature);
    void setRightTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getLeftTypeSignature();
    TypeSignature* getRightTypeSignature();
    ASTBinaryArithmeticOperatorNode* getBinaryOperator();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_ARITHMETIC_EXPRESSION_NODE_H
