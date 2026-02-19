//
// Created by Johny Georges on 2026-02-16.
//

#ifndef JETLANG_AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-statement-node.h"
#include "../ast-ref-value-assignment-node.h"

class ASTRefValueAssignmentStatementNode : public ASTStatementNode {
private:
    ASTRefValueAssignmentNode* _assignment;
    ASTExpressionNode* _expression;
public:
    ASTRefValueAssignmentStatementNode(ASTRefValueAssignmentNode* assignment, ASTExpressionNode* expression);
    ASTRefValueAssignmentNode* getVariableAssignment();
    ASTExpressionNode* getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
