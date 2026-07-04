//
// Created by Johny Georges on 2024-04-13.
//

#include "use-single-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-use-single-module-declaration-node.h"

std::shared_ptr<ASTNode> UseSingleModuleDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to use single module declaration since nodes list is not 4");
    }
    return std::make_shared<ASTUseSingleModuleDeclarationNode>(
            std::dynamic_pointer_cast<ASTUseNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTImportModuleNameNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFromNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTImportPathNode>(nodes[3])
    );
}