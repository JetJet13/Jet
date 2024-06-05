//
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-spread-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-spread-item-node.h"

ASTNode* ImportModuleListSpreadItemReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to import module list spread item since nodes list is not of size 2");
    }

    return new ASTImportModuleListSpreadItemNode(
            (ASTImportSpreadNode*)nodes[0],
            (ASTImportModuleNameNode*)nodes[1]
    );
}