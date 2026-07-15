//
// Created by Johny Georges on 2026-06-26.
//

#include "module-access-shared-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-access-shared-value-assignment-node.h"

std::shared_ptr<ASTNode> ModuleAccessSharedValueAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module access ref assignment since nodes list is not 2");
    }
    return std::make_shared<ASTModuleAccessSharedValueAssignmentNode>(
            std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTSharedValueAssignmentOperatorNode>(nodes[1])
    );
}