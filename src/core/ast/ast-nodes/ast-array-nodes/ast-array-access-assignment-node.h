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
    std::shared_ptr<ASTArrayAccessExpressionNode> _arrayAccessExpression;
    std::shared_ptr<ASTAssignmentOperatorNode> _assignmentOperator;
public:
    explicit ASTArrayAccessAssignmentNode(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTArrayAccessExpressionNode> getArrayAccess();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_ASSIGNMENT_NODE_H
