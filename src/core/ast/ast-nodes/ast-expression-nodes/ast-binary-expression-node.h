//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BINARY_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"

class ASTBinaryExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    ASTBinaryOperatorNode* _binaryOperator;
public:
    ASTBinaryExpressionNode(ASTExpressionNode* leftNode, ASTBinaryOperatorNode* binaryOperator, ASTExpressionNode* rightNode);
    ASTExpressionNode* getLeftNode();
    ASTExpressionNode* getRightNode();
    void setLeftNode(ASTExpressionNode* node);
    void setRightNode(ASTExpressionNode* node);
    ASTBinaryOperatorNode* getBinaryOperator();
    void markAsReferenced() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_EXPRESSION_NODE_H
