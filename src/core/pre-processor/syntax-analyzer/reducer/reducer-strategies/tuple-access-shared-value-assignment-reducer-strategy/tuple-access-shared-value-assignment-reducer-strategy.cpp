//
// Created by Johny Georges on 2026-06-26.
//

#include "tuple-access-shared-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-shared-value-assignment-node.h"

std::shared_ptr<ASTNode> TupleAccessSharedValueAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access ref assignment since nodes list is not 2");
    }
    return std::make_shared<ASTTupleAccessSharedValueAssignmentNode>(
            std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTSharedValueAssignmentOperatorNode>(nodes[1])
    );
}