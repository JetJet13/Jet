//
// Created by Johny Georges on 2024-06-01.
//

#include "import-many-by-wildcard-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-by-wildcard-module-declaration-node.h"

ASTNode* ImportManyByWildcardModuleDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to import many module declaration since nodes list is not 4");
    }

    return new ASTImportManyByWildcardModuleDeclarationNode(
        (ASTImportNode*)nodes[0],
        (ASTImportModuleListByWildcardItemNode*)nodes[1],
        (ASTFromNode*)nodes[2],
        (ASTImportPathNode*)nodes[3]
    );


}