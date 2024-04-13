//
// Created by Johny Georges on 2024-04-13.
//

#include "import-single-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"

ASTNode* ImportSingleModuleDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to import single module declaration since nodes list is not 4");
    }
    return new ASTImportSingleModuleDeclarationNode(
            (ASTImportModuleNameNode*)nodes[1],
            (ASTImportPathNode*)nodes[3]
    );
}