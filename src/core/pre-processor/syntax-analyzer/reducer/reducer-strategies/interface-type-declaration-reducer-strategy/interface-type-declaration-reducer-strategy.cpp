//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-type-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"

std::shared_ptr<ASTNode> InterfaceTypeDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to interface type declaration since nodes list is not of size 2 or 3");
    }

    if (nodes.size() == 2) {
        return std::make_shared<ASTInterfaceTypeDeclarationNode>(
                std::dynamic_pointer_cast<ASTInterfaceDefinitionNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTInterfacePropertyListNode>(nodes[1])
        );
    }

    return std::make_shared<ASTInterfaceTypeDeclarationNode>(
            std::dynamic_pointer_cast<ASTInterfaceDefinitionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTInterfacePropertyListNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}