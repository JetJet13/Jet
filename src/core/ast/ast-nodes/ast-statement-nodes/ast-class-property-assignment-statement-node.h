//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "../ast-class-nodes/ast-class-property-name-node.h"
#include "../ast-class-nodes/ast-class-property-assignment-node.h"
#include "ast-statement-node.h"

class ASTClassPropertyAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTClassPropertyAssignmentNode> _propertyAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTClassPropertyAssignmentStatementNode(std::shared_ptr<ASTClassPropertyAssignmentNode> propertyAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTClassPropertyAssignmentNode> getPropertyAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
