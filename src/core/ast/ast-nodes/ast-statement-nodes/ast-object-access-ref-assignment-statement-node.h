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
    ASTObjectAccessRefAssignmentNode* _objectAccessAssignment;
    ASTExpressionNode* _expression;
public:
    ASTObjectAccessRefAssignmentStatementNode(ASTObjectAccessRefAssignmentNode* objectAccessAssignment, ASTExpressionNode* expression);
    ASTObjectAccessRefAssignmentNode* getObjectAccessAssignment();
    ASTExpressionNode* getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
