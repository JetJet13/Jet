//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-assignment-node.h"

std::shared_ptr<ASTNode> ObjectAccessAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access assignment since nodes list is not 2");
    }
    return std::make_shared<ASTObjectAccessAssignmentNode>(
            std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
    );
}