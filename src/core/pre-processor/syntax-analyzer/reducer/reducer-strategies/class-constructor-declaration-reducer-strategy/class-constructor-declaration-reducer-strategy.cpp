//
// Created by Johny Georges on 2024-04-21.
//

#include "class-constructor-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"

std::shared_ptr<ASTNode> ClassConstructorDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class constructor declaration since nodes list is not of size 3");
    }

    return std::make_shared<ASTClassConstructorDeclarationNode>(
            std::dynamic_pointer_cast<ASTConstructorNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[2])
    );
}