//
// Created by Johny Georges on 2025-08-27.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "../ast-expression-nodes/ast-object-access-expression-node.h"

class ASTObjectAccessAssignmentNode : public ASTNode {
private:
    ASTObjectAccessExpressionNode* _objectAccessExpression;
    ASTAssignmentOperatorNode* _assignmentOperator;
public:
    explicit ASTObjectAccessAssignmentNode(ASTObjectAccessExpressionNode* objectAccessExpression, ASTAssignmentOperatorNode* assignmentOperator);
    ASTObjectAccessExpressionNode* getObjectAccess();
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_NODE_H
