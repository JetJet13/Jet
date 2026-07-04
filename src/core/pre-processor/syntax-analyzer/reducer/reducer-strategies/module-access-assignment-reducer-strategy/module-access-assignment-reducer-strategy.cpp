//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-access-assignment-node.h"

std::shared_ptr<ASTNode> ModuleAccessAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module access assignment since nodes list is not 2");
    }
    return std::make_shared<ASTModuleAccessAssignmentNode>(
            std::dynamic_pointer_cast<ASTModuleAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
    );
}