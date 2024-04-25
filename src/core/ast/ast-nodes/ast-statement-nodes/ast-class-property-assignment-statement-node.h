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

class ASTClassPropertyAssignmentStatementNode : public ASTNode {
private:
    ASTClassPropertyAssignmentNode* _propertyAssignment;
    ASTExpressionNode* _expression;
public:
    ASTClassPropertyAssignmentStatementNode(ASTClassPropertyAssignmentNode* propertyAssignment, ASTExpressionNode* expression);
    ASTClassPropertyAssignmentNode* getPropertyAssignment();
    ASTExpressionNode* getExpression();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE_H
