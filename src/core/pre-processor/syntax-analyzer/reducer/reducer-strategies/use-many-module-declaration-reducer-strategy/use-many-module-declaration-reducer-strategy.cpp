//
// Created by Johny Georges on 2024-04-16.
//

#include "use-many-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-use-many-module-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"

std::shared_ptr<ASTNode> UseManyModuleDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to use many module declaration since nodes list is not 4");
    }

    return std::make_shared<ASTUseManyModuleDeclarationNode>(
            std::dynamic_pointer_cast<ASTUseNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTImportModuleListByGroupItemNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFromNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTImportPathNode>(nodes[3])
    );
}