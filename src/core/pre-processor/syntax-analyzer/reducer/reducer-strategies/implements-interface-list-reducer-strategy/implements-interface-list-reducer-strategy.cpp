//
// Created by Johny Georges on 2025-07-05.
//

#include "implements-interface-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-list-node.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-name-last-node.h"

ASTNode* ImplementsInterfaceListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto implementsInterfaceListNode = new ASTImplementsInterfaceListNode((ASTImplementsNode*)nodes[0]);
    for (auto node : nodes) {
        if (node->is(AST_IMPLEMENTS_INTERFACE_NAME_NODE)) {
            implementsInterfaceListNode->addInterface((ASTImplementsInterfaceNameNode*)node);
        }

        if (node->is(AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE)) {
            implementsInterfaceListNode->addInterface(((ASTImplementsInterfaceNameLastNode*)node)->convertToInterfaceName());
        }

        if (node->is(AST_COMMA_NODE)) {
            implementsInterfaceListNode->addComma((ASTCommaNode*)node);
        }
    }
    return implementsInterfaceListNode;
}