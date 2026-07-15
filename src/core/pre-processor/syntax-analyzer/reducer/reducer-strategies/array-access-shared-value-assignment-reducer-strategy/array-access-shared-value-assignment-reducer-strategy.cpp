//
// Created by Johny Georges on 2026-06-26.
//

#include "array-access-shared-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-access-shared-value-assignment-node.h"

std::shared_ptr<ASTNode> ArrayAccessSharedValueAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access ref assignment since nodes list is not 2");
    }
    return std::make_shared<ASTArrayAccessSharedValueAssignmentNode>(
            std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTSharedValueAssignmentOperatorNode>(nodes[1])
    );
}