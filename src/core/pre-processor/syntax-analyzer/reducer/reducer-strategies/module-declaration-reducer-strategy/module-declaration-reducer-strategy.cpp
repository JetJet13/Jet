//
// Created by Johny Georges on 2024-04-13.
//

#include "module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

std::shared_ptr<ASTNode> ModuleDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module list alias item since nodes list is not of size 2");
    }

    return std::make_shared<ASTModuleDeclarationNode>(
            std::dynamic_pointer_cast<ASTModuleNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTModuleNameNode>(nodes[1])
    );
}