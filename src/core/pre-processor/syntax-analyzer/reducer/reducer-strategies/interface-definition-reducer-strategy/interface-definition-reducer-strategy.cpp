//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-definition-node.h"

std::shared_ptr<ASTNode> InterfaceDefinitionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to interface definition since nodes list is not of size 2");
    }

    return std::make_shared<ASTInterfaceDefinitionNode>(
            std::dynamic_pointer_cast<ASTInterfaceNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTInterfaceNameNode>(nodes[1])
    );
}