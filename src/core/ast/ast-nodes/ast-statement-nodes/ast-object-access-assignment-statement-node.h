//
// Created by Johny Georges on 2025-08-27.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-object-nodes/ast-object-access-assignment-node.h"
#include "ast-statement-node.h"

class ASTObjectAccessAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTObjectAccessAssignmentNode> _objectAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTObjectAccessAssignmentStatementNode(std::shared_ptr<ASTObjectAccessAssignmentNode> objectAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTObjectAccessAssignmentNode> getObjectAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
