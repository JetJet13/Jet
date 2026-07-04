//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-object-nodes/ast-object-access-ref-assignment-node.h"

class ASTObjectAccessRefAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTObjectAccessRefAssignmentNode> _objectAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTObjectAccessRefAssignmentStatementNode(std::shared_ptr<ASTObjectAccessRefAssignmentNode> objectAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTObjectAccessRefAssignmentNode> getObjectAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
