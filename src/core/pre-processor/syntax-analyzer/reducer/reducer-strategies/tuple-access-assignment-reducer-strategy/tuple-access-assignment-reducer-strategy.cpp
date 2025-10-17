//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-assignment-node.h"

ASTNode* TupleAccessAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access assignment since nodes list is not 2");
    }
    return new ASTTupleAccessAssignmentNode(
            (ASTTupleAccessExpressionNode*)nodes[0],
            (ASTAssignmentOperatorNode*)nodes[1]
    );
}