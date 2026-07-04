//
// Created by Johny Georges on 2026-06-26.
//

#include "object-access-ref-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-ref-assignment-node.h"

std::shared_ptr<ASTNode> ObjectAccessRefAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access ref assignment since nodes list is not 2");
    }
    return std::make_shared<ASTObjectAccessRefAssignmentNode>(
            std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTRefValueAssignmentOperatorNode>(nodes[1])
    );
}