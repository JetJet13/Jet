//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-array-nodes/ast-array-access-assignment-node.h"
#include "ast-statement-node.h"

class ASTArrayAccessAssignmentStatementNode : public ASTStatementNode {
private:
    ASTArrayAccessAssignmentNode* _arrayAccessAssignment;
    ASTExpressionNode* _expression;
public:
    ASTArrayAccessAssignmentStatementNode(ASTArrayAccessAssignmentNode* arrayAccessAssignment, ASTExpressionNode* expression);
    ASTArrayAccessAssignmentNode* getArrayAccessAssignment();
    ASTExpressionNode* getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
