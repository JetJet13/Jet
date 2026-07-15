//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-shared-value-assignment-node.h"

class ASTTupleAccessSharedValueAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTTupleAccessSharedValueAssignmentNode> _tupleAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTTupleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTTupleAccessSharedValueAssignmentNode> tupleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTTupleAccessSharedValueAssignmentNode> getTupleAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
