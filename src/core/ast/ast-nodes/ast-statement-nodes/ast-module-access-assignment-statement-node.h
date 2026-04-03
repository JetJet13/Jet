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
    ASTModuleAccessAssignmentNode* _moduleAccessAssignment;
    ASTExpressionNode* _expression;
public:
    ASTModuleAccessAssignmentStatementNode(ASTModuleAccessAssignmentNode* moduleAccessAssignment, ASTExpressionNode* expression);
    ASTModuleAccessAssignmentNode* getModuleAccessAssignment();
    ASTExpressionNode* getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
