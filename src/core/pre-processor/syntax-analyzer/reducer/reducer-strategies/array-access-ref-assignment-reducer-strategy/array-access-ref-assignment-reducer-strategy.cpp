//
// Created by Johny Georges on 2026-06-26.
//

#include "array-access-ref-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-access-ref-assignment-node.h"

ASTNode* ArrayAccessRefAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access ref assignment since nodes list is not 2");
    }
    return new ASTArrayAccessRefAssignmentNode(
            (ASTArrayAccessExpressionNode*)nodes[0],
            (ASTRefValueAssignmentOperatorNode*)nodes[1]
    );
}