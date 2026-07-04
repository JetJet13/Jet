//
// Created by Johny Georges on 2024-06-01.
//

#include "import-many-by-wildcard-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-by-wildcard-module-declaration-node.h"

std::shared_ptr<ASTNode> ImportManyByWildcardModuleDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to import many module declaration since nodes list is not 4");
    }

    return std::make_shared<ASTImportManyByWildcardModuleDeclarationNode>(
        std::dynamic_pointer_cast<ASTImportNode>(nodes[0]),
        std::dynamic_pointer_cast<ASTImportModuleListByWildcardItemNode>(nodes[1]),
        std::dynamic_pointer_cast<ASTFromNode>(nodes[2]),
        std::dynamic_pointer_cast<ASTImportPathNode>(nodes[3])
    );


}