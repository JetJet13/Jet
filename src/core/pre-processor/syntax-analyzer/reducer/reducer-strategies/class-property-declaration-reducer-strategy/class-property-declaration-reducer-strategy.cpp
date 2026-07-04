//
// Created by Johny Georges on 2024-04-20.
//

#include "class-property-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"

std::shared_ptr<ASTNode> ClassPropertyDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTClassPropertyDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassPropertyInitNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
        );
    }

    if (nodes.size() == 1) {
        return std::make_shared<ASTClassPropertyDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassPropertyInitNode>(nodes[0])
        );
    }
    throw std::invalid_argument("unable to reduce to class property since nodes list size is not 2 or 1");

}