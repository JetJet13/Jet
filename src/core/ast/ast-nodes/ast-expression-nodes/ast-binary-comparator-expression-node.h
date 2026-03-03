//
// Created by Johny Georges on 2026-03-02.
//

#ifndef JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"

class ASTBinaryComparatorExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    ASTBinaryComparatorOperatorNode* _binaryOperator;
    TypeSignature* _leftTypeSignature = new UnknownTypeSignature();
    TypeSignature* _rightTypeSignature = new UnknownTypeSignature();
public:
    ASTBinaryComparatorExpressionNode(ASTExpressionNode* leftNode, ASTBinaryComparatorOperatorNode* binaryOperator, ASTExpressionNode* rightNode);
    ASTExpressionNode* getLeftNode();
    ASTExpressionNode* getRightNode();
    void setLeftTypeSignature(TypeSignature* typeSignature);
    void setRightTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getLeftTypeSignature();
    TypeSignature* getRightTypeSignature();
    ASTBinaryComparatorOperatorNode* getBinaryOperator();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H
