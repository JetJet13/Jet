//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_REF_ASSIGNMENT_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_REF_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-array-access-node.h"
#include "../ast-expression-nodes/ast-array-access-expression-node.h"
#include "../ast-operator-nodes/ast-ref-value-assignment-operator-node.h"

class ASTArrayAccessRefAssignmentNode : public ASTNode {
private:
    ASTArrayAccessExpressionNode* _arrayAccessExpression;
    ASTRefValueAssignmentOperatorNode* _assignmentOperator;
public:
    explicit ASTArrayAccessRefAssignmentNode(ASTArrayAccessExpressionNode* arrayAccessExpression, ASTRefValueAssignmentOperatorNode* assignmentOperator);
    ASTArrayAccessExpressionNode* getArrayAccess();
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_REF_ASSIGNMENT_NODE_H
