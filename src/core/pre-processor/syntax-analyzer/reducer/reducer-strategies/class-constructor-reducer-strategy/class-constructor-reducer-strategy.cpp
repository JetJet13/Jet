//
// Created by Johny Georges on 2024-04-21.
//

#include "class-constructor-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-constructor-node.h"

ASTNode* ClassConstructorReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class constructor declaration since nodes list is not of size 3");
    }

    return new ASTClassConstructorNode(
            (ASTFunctionParameterListNode*)nodes[1],
            (ASTFunctionBlockNode*)nodes[2]
    );
}