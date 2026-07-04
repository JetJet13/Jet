//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-statement-node.h"
#include "../ast-class-nodes/ast-class-property-ref-value-assignment-node.h"

class ASTClassPropertyRefValueAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTClassPropertyRefValueAssignmentNode> _propertyAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTClassPropertyRefValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertyRefValueAssignmentNode> propertyAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTClassPropertyRefValueAssignmentNode> getPropertyAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE_H
