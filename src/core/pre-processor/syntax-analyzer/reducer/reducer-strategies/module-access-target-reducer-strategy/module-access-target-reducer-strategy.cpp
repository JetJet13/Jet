//
// Created by Johny Georges on 2024-11-05.
//

#include "module-access-target-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-access-target-node.h"

ASTNode* ModuleAccessTargetReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to module access target since nodes list is not 1");
    }

    return new ASTModuleAccessTargetNode(
            (ASTIdentifierExpressionNode*)nodes[0]
    );
}