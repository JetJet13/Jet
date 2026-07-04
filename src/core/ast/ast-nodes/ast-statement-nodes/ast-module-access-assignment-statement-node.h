//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-object-nodes/ast-object-access-assignment-node.h"
#include "ast-statement-node.h"
#include "../ast-module-nodes/ast-module-access-assignment-node.h"

class ASTModuleAccessAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTModuleAccessAssignmentNode> _moduleAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTModuleAccessAssignmentStatementNode(std::shared_ptr<ASTModuleAccessAssignmentNode> moduleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTModuleAccessAssignmentNode> getModuleAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
