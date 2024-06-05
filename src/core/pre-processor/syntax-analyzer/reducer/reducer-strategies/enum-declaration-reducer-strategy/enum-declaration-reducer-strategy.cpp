//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

ASTNode* EnumDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to enum declaration since nodes list is not of size 3");
    }

    return new ASTEnumDeclarationNode(
            (ASTEnumNode*)nodes[0],
            (ASTEnumNameNode*)nodes[1],
            (ASTEnumKeyValueListNode*)nodes[2]
    );
}