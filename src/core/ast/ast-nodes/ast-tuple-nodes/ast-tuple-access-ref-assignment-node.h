//
// Created by Johny Georges on 2026-06-26.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_REF_ASSIGNMENT_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_REF_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-tuple-access-expression.h"
#include "../ast-operator-nodes/ast-ref-value-assignment-operator-node.h"

class ASTTupleAccessRefAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTTupleAccessExpressionNode> _tupleAccessExpression;
    std::shared_ptr<ASTRefValueAssignmentOperatorNode> _assignmentOperator;
public:
    explicit ASTTupleAccessRefAssignmentNode(std::shared_ptr<ASTTupleAccessExpressionNode> tupleAccessExpression, std::shared_ptr<ASTRefValueAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTTupleAccessExpressionNode> getTupleAccess();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_REF_ASSIGNMENT_NODE_H
