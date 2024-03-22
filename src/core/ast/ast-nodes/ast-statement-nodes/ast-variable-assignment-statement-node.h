//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"

class ASTVariableAssignmentStatementNode : public ASTNode {
private:
    ASTVariableAssignmentNode* _variable;
    ASTExpressionNode* _expression;
public:
    ASTVariableAssignmentStatementNode(ASTVariableAssignmentNode* variable, ASTExpressionNode* expression);
    ASTVariableAssignmentNode* getVariable();
    ASTExpressionNode* getExpression();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE_H
