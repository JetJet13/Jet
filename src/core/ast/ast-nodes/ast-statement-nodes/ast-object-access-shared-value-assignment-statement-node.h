//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-object-nodes/ast-object-access-shared-value-assignment-node.h"

class ASTObjectAccessSharedValueAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTObjectAccessSharedValueAssignmentNode> _objectAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTObjectAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTObjectAccessSharedValueAssignmentNode> objectAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTObjectAccessSharedValueAssignmentNode> getObjectAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
