//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-module-nodes/ast-module-access-shared-value-assignment-node.h"

class ASTModuleAccessSharedValueAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTModuleAccessSharedValueAssignmentNode> _moduleAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTModuleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTModuleAccessSharedValueAssignmentNode> moduleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTModuleAccessSharedValueAssignmentNode> getModuleAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
