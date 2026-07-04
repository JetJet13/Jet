//
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-alias-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-alias-item-node.h"

std::shared_ptr<ASTNode> ImportModuleListAliasItemReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to import module list alias item since nodes list is not of size 3");
    }

    return std::make_shared<ASTImportModuleListAliasItemNode>(
            std::dynamic_pointer_cast<ASTImportModuleNameNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAsNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTImportModuleAliasNameNode>(nodes[2])
    );
}