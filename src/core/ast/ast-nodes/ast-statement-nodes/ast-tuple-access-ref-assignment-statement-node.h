//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-ref-assignment-node.h"

class ASTTupleAccessRefAssignmentStatementNode : public ASTStatementNode {
private:
    ASTTupleAccessRefAssignmentNode* _tupleAccessAssignment;
    ASTExpressionNode* _expression;
public:
    ASTTupleAccessRefAssignmentStatementNode(ASTTupleAccessRefAssignmentNode* tupleAccessAssignment, ASTExpressionNode* expression);
    ASTTupleAccessRefAssignmentNode* getTupleAccessAssignment();
    ASTExpressionNode* getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE_H
