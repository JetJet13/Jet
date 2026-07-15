//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-array-access-node.h"
#include "../ast-expression-nodes/ast-array-access-expression-node.h"
#include "../ast-operator-nodes/ast-shared-value-assignment-operator-node.h"

class ASTArrayAccessSharedValueAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTArrayAccessExpressionNode> _arrayAccessExpression;
    std::shared_ptr<ASTSharedValueAssignmentOperatorNode> _assignmentOperator;
public:
    explicit ASTArrayAccessSharedValueAssignmentNode(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTArrayAccessExpressionNode> getArrayAccess();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE_H
