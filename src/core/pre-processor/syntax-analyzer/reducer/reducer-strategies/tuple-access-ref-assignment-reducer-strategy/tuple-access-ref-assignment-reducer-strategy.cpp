//
// Created by Johny Georges on 2026-06-26.
//

#include "tuple-access-ref-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-ref-assignment-node.h"

ASTNode* TupleAccessRefAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access ref assignment since nodes list is not 2");
    }
    return new ASTTupleAccessRefAssignmentNode(
            (ASTTupleAccessExpressionNode*)nodes[0],
            (ASTRefValueAssignmentOperatorNode*)nodes[1]
    );
}