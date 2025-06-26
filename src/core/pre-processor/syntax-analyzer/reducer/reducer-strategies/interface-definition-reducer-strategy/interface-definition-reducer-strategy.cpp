//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-definition-node.h"

ASTNode* InterfaceDefinitionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to interface definition since nodes list is not of size 4");
    }

    return new ASTInterfaceDefinitionNode(
            (ASTInterfaceNode*)nodes[0],
            (ASTInterfaceNameNode*)nodes[1]
    );
}