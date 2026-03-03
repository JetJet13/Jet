//
// Created by Johny Georges on 2025-06-07.
//

#ifndef JETLANG_AST_CONCAT_EXPRESSION_NODE_H
#define JETLANG_AST_CONCAT_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-concat-node.h"

class ASTConcatExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _leftNode;
    ASTExpressionNode* _rightNode;
    ASTConcatNode* _concatNode;
public:
    ASTConcatExpressionNode(ASTExpressionNode* leftNode, ASTConcatNode* concatNode, ASTExpressionNode* rightNode);
    ASTExpressionNode* getLeftNode();
    ASTExpressionNode* getRightNode();
    ASTConcatNode* getConcatNode();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CONCAT_EXPRESSION_NODE_H
