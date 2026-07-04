//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_MODULE_ACCESS_REF_ASSIGNMENT_NODE_H
#define JETLANG_AST_MODULE_ACCESS_REF_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-module-access-expression-node.h"
#include "../ast-operator-nodes/ast-ref-value-assignment-operator-node.h"

class ASTModuleAccessRefAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTModuleAccessExpressionNode> _moduleAccessExpression;
    std::shared_ptr<ASTRefValueAssignmentOperatorNode> _assignmentOperator;
public:
    explicit ASTModuleAccessRefAssignmentNode(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, std::shared_ptr<ASTRefValueAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTModuleAccessExpressionNode> getModuleAccess();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_REF_ASSIGNMENT_NODE_H
