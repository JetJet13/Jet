//
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-by-group-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"

std::shared_ptr<ASTNode> ImportModuleListByGroupItemReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to import module list by group item since nodes list is not 3");
    }
    return std::make_shared<ASTImportModuleListByGroupItemNode>(
            std::dynamic_pointer_cast<ASTImportModuleNameNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTModuleAccessNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTImportModuleListNode>(nodes[2])
    );
}