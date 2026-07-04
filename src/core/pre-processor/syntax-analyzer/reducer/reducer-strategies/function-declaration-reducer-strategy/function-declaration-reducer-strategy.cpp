//
// Created by Johny Georges on 2024-03-18.
//

#include "function-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"

std::shared_ptr<ASTNode> FunctionDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to function declaration since nodes list is not of size 2 or 3");
    }

    if (nodes.size() == 2) {
        return std::make_shared<ASTFunctionDeclarationNode>(
                std::dynamic_pointer_cast<ASTFunctionDefinitionNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[1])
        );
    }

    return std::make_shared<ASTFunctionDeclarationNode>(
            std::dynamic_pointer_cast<ASTFunctionDefinitionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}