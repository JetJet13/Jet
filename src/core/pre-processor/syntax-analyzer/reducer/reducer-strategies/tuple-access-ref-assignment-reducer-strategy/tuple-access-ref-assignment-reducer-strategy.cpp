//
// Created by Johny Georges on 2026-06-26.
//

#include "tuple-access-ref-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-ref-assignment-node.h"

std::shared_ptr<ASTNode> TupleAccessRefAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access ref assignment since nodes list is not 2");
    }
    return std::make_shared<ASTTupleAccessRefAssignmentNode>(
            std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTRefValueAssignmentOperatorNode>(nodes[1])
    );
}