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
    std::shared_ptr<ASTRefValueAssignmentNode> _assignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTRefValueAssignmentStatementNode(std::shared_ptr<ASTRefValueAssignmentNode> assignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTRefValueAssignmentNode> getVariableAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
