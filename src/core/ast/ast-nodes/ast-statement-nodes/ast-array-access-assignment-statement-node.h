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
    std::shared_ptr<ASTArrayAccessAssignmentNode> _arrayAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTArrayAccessAssignmentStatementNode(std::shared_ptr<ASTArrayAccessAssignmentNode> arrayAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTArrayAccessAssignmentNode> getArrayAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
