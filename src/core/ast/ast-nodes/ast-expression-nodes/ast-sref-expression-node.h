//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_AST_SREF_EXPRESSION_NODE_H
#define JETLANG_AST_SREF_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-sref-node.h"

class ASTSrefExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _expression;
    ASTSrefNode* _srefNode;
public:
    ASTSrefExpressionNode(ASTSrefNode* srefNode, ASTExpressionNode* astExpressionNode);
    ASTExpressionNode* getExpressionNode();
    ASTSrefNode* getSrefNode();
    void markAsReferenced() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_SREF_EXPRESSION_NODE_H
