//
// Created by Johny Georges on 2024-11-05.
//

#include "module-access-target-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-access-target-node.h"

std::shared_ptr<ASTNode> ModuleAccessTargetReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to module access target since nodes list is not 1");
    }

    return std::make_shared<ASTModuleAccessTargetNode>(
            std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0])
    );
}