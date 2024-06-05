//
// Created by Johny Georges on 2024-04-13.
//

#include "use-single-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-use-single-module-declaration-node.h"

ASTNode* UseSingleModuleDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to use single module declaration since nodes list is not 4");
    }
    return new ASTUseSingleModuleDeclarationNode(
            (ASTUseNode*)nodes[0],
            (ASTImportModuleNameNode*)nodes[1],
            (ASTFromNode*)nodes[2],
            (ASTImportPathNode*)nodes[3]
    );
}