//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-type-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"

ASTNode* InterfaceTypeDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to interface type declaration since nodes list is not of size 2 or 3");
    }

    if (nodes.size() == 2) {
        return new ASTInterfaceTypeDeclarationNode(
                (ASTInterfaceDefinitionNode*)nodes[0],
                (ASTInterfacePropertyListNode*)nodes[1]
        );
    }

    return new ASTInterfaceTypeDeclarationNode(
            (ASTInterfaceDefinitionNode*)nodes[1],
            (ASTInterfacePropertyListNode*)nodes[2],
            (ASTExportNode*)nodes[0]
    );
}