//
// Created by Johny Georges on 2025-01-15.
//

#ifndef JETLANG_AST_DREF_EXPRESSION_NODE_H
#define JETLANG_AST_DREF_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-dref-node.h"

class ASTDrefExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _expression;
    ASTDrefNode* _drefNode;
public:
    ASTDrefExpressionNode(ASTDrefNode* drefNode, ASTExpressionNode* astExpressionNode);
    ASTExpressionNode* getExpressionNode();
    ASTDrefNode* getDrefNode();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_DREF_EXPRESSION_NODE_H
