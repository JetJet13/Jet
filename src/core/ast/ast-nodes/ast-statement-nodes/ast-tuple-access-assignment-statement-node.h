//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-statement-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-assignment-node.h"

class ASTTupleAccessAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTTupleAccessAssignmentNode> _tupleAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTTupleAccessAssignmentStatementNode(std::shared_ptr<ASTTupleAccessAssignmentNode> tupleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTTupleAccessAssignmentNode> getTupleAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
