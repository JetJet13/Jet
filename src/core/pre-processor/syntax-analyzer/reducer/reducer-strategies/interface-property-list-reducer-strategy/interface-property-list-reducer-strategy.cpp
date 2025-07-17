//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-property-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-property-list-node.h"

ASTNode* InterfacePropertyListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto interfacePropertyListNode = new ASTInterfacePropertyListNode((ASTInterfaceStartNode*)nodes[0], (ASTInterfaceEndNode*)nodes[nodes.size() - 1]);
    for (int i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_INTERFACE_PROPERTY_NODE)) {
            interfacePropertyListNode->addProperty((ASTInterfacePropertyNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            interfacePropertyListNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to interface property list since node list is malformed");
        }
    }

    return interfacePropertyListNode;
}