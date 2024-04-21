//
// Created by Johny Georges on 2024-04-21.
//

#include "class-constructor-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"

ASTNode* ClassConstructorDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class constructor declaration since nodes list is not of size 3");
    }

    return new ASTClassConstructorDeclarationNode(
            (ASTFunctionParameterListNode*)nodes[1],
            (ASTFunctionBlockNode*)nodes[2]
    );
}