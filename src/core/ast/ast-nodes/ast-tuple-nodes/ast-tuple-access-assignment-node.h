//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_ASSIGNMENT_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "../ast-expression-nodes/ast-tuple-access-expression.h"

class ASTTupleAccessAssignmentNode : public ASTNode {
private:
    ASTTupleAccessExpressionNode* _tupleAccessExpression;
    ASTAssignmentOperatorNode* _assignmentOperator;
public:
    explicit ASTTupleAccessAssignmentNode(ASTTupleAccessExpressionNode* tupleAccessExpression, ASTAssignmentOperatorNode* assignmentOperator);
    ASTTupleAccessExpressionNode* getTupleAccess();
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_ASSIGNMENT_NODE_H
