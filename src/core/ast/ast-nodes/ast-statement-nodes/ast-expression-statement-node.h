//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_EXPRESSION_STATEMENT_NODE_H
#define JETLANG_AST_EXPRESSION_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "ast-statement-node.h"

class ASTExpressionStatementNode : public ASTStatementNode {
private:
    ASTExpressionNode* _expression;
public:
    ASTExpressionStatementNode(ASTExpressionNode* expression);
    ASTExpressionNode* getExpression();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_EXPRESSION_STATEMENT_NODE_H
