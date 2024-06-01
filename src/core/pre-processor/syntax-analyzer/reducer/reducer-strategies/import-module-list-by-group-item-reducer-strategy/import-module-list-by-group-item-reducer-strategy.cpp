//
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-by-group-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"

ASTNode* ImportModuleListByGroupItemReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to import module list by group item since nodes list is not 3");
    }
    return new ASTImportModuleListByGroupItemNode(
            (ASTImportModuleNameNode*)nodes[0],
            (ASTModuleAccessNode*)nodes[1],
            (ASTImportModuleListNode*)nodes[2]
    );
}