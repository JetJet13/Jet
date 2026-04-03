//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_NODE_H
#define JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "../ast-expression-nodes/ast-module-access-expression-node.h"

class ASTModuleAccessAssignmentNode : public ASTNode {
private:
    ASTModuleAccessExpressionNode* _moduleAccessExpression;
    ASTAssignmentOperatorNode* _assignmentOperator;
public:
    explicit ASTModuleAccessAssignmentNode(ASTModuleAccessExpressionNode* moduleAccessExpression, ASTAssignmentOperatorNode* assignmentOperator);
    ASTModuleAccessExpressionNode* getModuleAccess();
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_NODE_H
