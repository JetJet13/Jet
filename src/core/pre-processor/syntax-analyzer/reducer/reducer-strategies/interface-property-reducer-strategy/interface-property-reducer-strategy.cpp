//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-property-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-property-node.h"

ASTNode* InterfacePropertyReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to interface property since nodes list is not of size 3 or 1");
    }

    return new ASTInterfacePropertyNode(
            (ASTIdentifierExpressionNode*)nodes[0],
            (ASTTypeColonNode*)nodes[1],
            (ASTTypeNode*)nodes[2]
    );
}