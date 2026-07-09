//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "ast-statement-node.h"

class ASTVariableAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTVariableAssignmentNode> _variableAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTVariableAssignmentStatementNode(std::shared_ptr<ASTVariableAssignmentNode> variable, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTVariableAssignmentNode> getVariableAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H
