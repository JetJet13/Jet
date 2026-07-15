//
// Created by Johny Georges on 2026-06-26.
//

#include "object-access-shared-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-shared-value-assignment-node.h"

std::shared_ptr<ASTNode> ObjectAccessSharedValueAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access ref assignment since nodes list is not 2");
    }
    return std::make_shared<ASTObjectAccessSharedValueAssignmentNode>(
            std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTSharedValueAssignmentOperatorNode>(nodes[1])
    );
}