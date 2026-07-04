//
// Created by Johny Georges on 2024-11-05.
//

#include "module-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

std::shared_ptr<ASTNode> ModuleAccessExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module access expression since nodes list is too short");
    }

    return std::make_shared<ASTModuleAccessExpressionNode>(
            std::dynamic_pointer_cast<ASTModuleAccessSourceNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTModuleAccessNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTModuleAccessTargetNode>(nodes[2])
    );
}