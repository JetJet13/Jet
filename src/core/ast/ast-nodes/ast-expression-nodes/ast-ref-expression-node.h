//
// Created by Johny Georges on 2025-01-15.
//

#ifndef JETLANG_AST_REF_EXPRESSION_NODE_H
#define JETLANG_AST_REF_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-base-nodes/ast-ref-base-node.h"

class ASTRefExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _expression;
    ASTRefBaseNode* _refNode;
public:
    ASTRefExpressionNode(ASTRefBaseNode* refNode, ASTExpressionNode* astExpressionNode);
    ASTExpressionNode* getExpressionNode();
    ASTRefBaseNode* getRefNode();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_EXPRESSION_NODE_H
