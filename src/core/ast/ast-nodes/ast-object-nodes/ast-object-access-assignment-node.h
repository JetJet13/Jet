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
    std::shared_ptr<ASTObjectAccessExpressionNode> _objectAccessExpression;
    std::shared_ptr<ASTAssignmentOperatorNode> _assignmentOperator;
public:
    explicit ASTObjectAccessAssignmentNode(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTObjectAccessExpressionNode> getObjectAccess();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_ASSIGNMENT_NODE_H
