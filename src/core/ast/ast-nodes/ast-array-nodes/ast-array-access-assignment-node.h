//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "ast-array-access-node.h"
#include "../ast-expression-nodes/ast-array-access-expression-node.h"

class ASTArrayAccessAssignmentNode : public ASTNode {
private:
    ASTArrayAccessExpressionNode* _arrayAccessExpression;
    ASTAssignmentOperatorNode* _assignmentOperator;
public:
    explicit ASTArrayAccessAssignmentNode(ASTArrayAccessExpressionNode* arrayAccessExpression, ASTAssignmentOperatorNode* assignmentOperator);
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

#endif //JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_NODE_H
