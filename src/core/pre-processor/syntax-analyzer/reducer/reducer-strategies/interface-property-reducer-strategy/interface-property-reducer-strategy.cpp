//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-property-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-property-node.h"

std::shared_ptr<ASTNode> InterfacePropertyReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to interface property since nodes list is not of size 3");
    }

    return std::make_shared<ASTInterfacePropertyNode>(
            std::dynamic_pointer_cast<ASTInterfacePropertyNameNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTInterfaceColonNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
    );
}