//
// Created by Johny Georges on 2024-04-15.
//

#include "import-module-list-by-wildcard-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"

ASTNode* ImportModuleListByWildcardItemReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to import module list by wildcard item since nodes list is not 3");
    }
    return new ASTImportModuleListByWildcardItemNode(
            (ASTImportModuleNameNode*)nodes[0],
            (ASTImportWildcardNode*)nodes[2]
    );
}