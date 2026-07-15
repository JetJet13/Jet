//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-statement-node.h"
#include "../ast-class-nodes/ast-class-property-shared-value-assignment-node.h"

class ASTClassPropertySharedValueAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTClassPropertySharedValueAssignmentNode> _propertyAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTClassPropertySharedValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertySharedValueAssignmentNode> propertyAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTClassPropertySharedValueAssignmentNode> getPropertyAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
