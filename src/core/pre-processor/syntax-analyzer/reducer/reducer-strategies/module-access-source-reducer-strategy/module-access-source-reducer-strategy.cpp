//
// Created by Johny Georges on 2024-11-05.
//

#include "module-access-source-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-access-source-node.h"

ASTNode* ModuleAccessSourceReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to module access source since nodes list is not 1");
    }

    return new ASTModuleAccessSourceNode(
            (ASTExpressionNode*)nodes[0]
    );
}