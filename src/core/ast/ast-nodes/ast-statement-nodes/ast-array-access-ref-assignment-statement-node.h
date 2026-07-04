//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-array-nodes/ast-array-access-ref-assignment-node.h"

class ASTArrayAccessRefAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTArrayAccessRefAssignmentNode> _arrayAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTArrayAccessRefAssignmentStatementNode(std::shared_ptr<ASTArrayAccessRefAssignmentNode> arrayAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTArrayAccessRefAssignmentNode> getArrayAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
