//
// Created by Johny Georges on 2024-04-13.
//

#include "module-list-alias-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-alias-item-node.h"

ASTNode* ModuleListAliasItemReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module list alias item since nodes list is not of size 3");
    }

    return new ASTModuleListAliasItemNode(
            (ASTModuleNameNode*)nodes[0],
            (ASTModuleAliasNameNode*)nodes[2]
    );
}