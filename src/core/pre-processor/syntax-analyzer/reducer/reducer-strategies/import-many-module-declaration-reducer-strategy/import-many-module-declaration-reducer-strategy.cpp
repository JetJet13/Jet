//
// Created by Johny Georges on 2024-04-15.
//

#include "import-many-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-module-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"

std::shared_ptr<ASTNode> ImportManyModuleDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to import many module declaration since nodes list is not 4");
    }


    return std::make_shared<ASTImportManyModuleDeclarationNode>(
            std::dynamic_pointer_cast<ASTImportNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTImportModuleListByGroupItemNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFromNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTImportPathNode>(nodes[3])
    );
}