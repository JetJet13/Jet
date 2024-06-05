//
// Created by Johny Georges on 2024-04-13.
//

#include "module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

ASTNode* ModuleDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module list alias item since nodes list is not of size 3");
    }

    return new ASTModuleDeclarationNode(
            (ASTModuleNode*)nodes[0],
            (ASTModuleNameNode*)nodes[1],
            (ASTModuleListNode*)nodes[2]
    );
}