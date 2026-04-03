//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-access-assignment-node.h"

ASTNode* ModuleAccessAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module access assignment since nodes list is not 2");
    }
    return new ASTModuleAccessAssignmentNode(
            (ASTModuleAccessExpressionNode*)nodes[0],
            (ASTAssignmentOperatorNode*)nodes[1]
    );
}