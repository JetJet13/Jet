//
// Created by Johny Georges on 2024-04-21.
//

#include "class-method-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"

std::shared_ptr<ASTNode> ClassMethodDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 3) {
        return std::make_shared<ASTClassMethodDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassMethodDefinitionNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[2])
        );
    }

    if (nodes.size() == 5) {
        return std::make_shared<ASTClassMethodDeclarationNode>(
                std::dynamic_pointer_cast<ASTClassMethodDefinitionNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[4]),
                std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[2]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[3])
        );
    }

    throw std::invalid_argument("unable to reduce to class method declaration since nodes list is not of size 3 or 5");
}