//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

std::shared_ptr<ASTNode> EnumDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3 && nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to enum declaration since nodes list is not of size 3");
    }

    if (nodes.size() == 3) {
        return std::make_shared<ASTEnumDeclarationNode>(
                std::dynamic_pointer_cast<ASTEnumNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTEnumNameNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTEnumKeyValueListNode>(nodes[2])
        );
    }

    return std::make_shared<ASTEnumDeclarationNode>(
            std::dynamic_pointer_cast<ASTEnumNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTEnumNameNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTEnumKeyValueListNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}