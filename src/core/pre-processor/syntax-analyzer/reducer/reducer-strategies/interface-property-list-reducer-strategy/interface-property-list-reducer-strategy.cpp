//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-property-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-property-list-node.h"

ASTNode* InterfacePropertyListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto interfacePropertyListNode = new ASTInterfacePropertyListNode((ASTInterfaceStartNode*)nodes[0], (ASTInterfaceEndNode*)nodes[nodes.size() - 1]);
    for (auto node : nodes) {
        if (node->is(AST_INTERFACE_PROPERTY_NODE)) {
            interfacePropertyListNode->addProperty((ASTInterfacePropertyNode*)node);
        }
        if (node->is(AST_COMMA_NODE)) {
            interfacePropertyListNode->addComma((ASTCommaNode*)node);
        }
    }
    return interfacePropertyListNode;
}