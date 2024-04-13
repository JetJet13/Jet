//
// Created by Johny Georges on 2024-04-13.
//

#include "module-list-spread-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-spread-item-node.h"

ASTNode* ModuleListSpreadItemReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module list spread item since nodes list is not of size 2");
    }

    return new ASTModuleListSpreadItemNode(
            (ASTModuleNameNode*)nodes[1]
    );
}