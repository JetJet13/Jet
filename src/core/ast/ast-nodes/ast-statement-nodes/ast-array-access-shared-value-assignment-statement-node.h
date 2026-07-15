//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-array-nodes/ast-array-access-shared-value-assignment-node.h"

class ASTArrayAccessSharedValueAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTArrayAccessSharedValueAssignmentNode> _arrayAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTArrayAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTArrayAccessSharedValueAssignmentNode> arrayAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTArrayAccessSharedValueAssignmentNode> getArrayAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
