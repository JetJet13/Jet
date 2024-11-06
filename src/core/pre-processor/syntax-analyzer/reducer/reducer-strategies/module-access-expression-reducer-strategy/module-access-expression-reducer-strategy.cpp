//
// Created by Johny Georges on 2024-11-05.
//

#include "module-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

ASTNode* ModuleAccessExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module access expression since nodes list is too short");
    }

    return new ASTModuleAccessExpressionNode(
            (ASTModuleAccessSourceNode*)nodes[0],
            (ASTModuleAccessNode*)nodes[1],
            (ASTModuleAccessTargetNode*)nodes[2]
    );
}