//
// Created by Johny Georges on 2025-07-05.
//

#include "implements-interface-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-list-node.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-name-last-node.h"

ASTNode* ImplementsInterfaceListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto implementsInterfaceListNode = new ASTImplementsInterfaceListNode((ASTImplementsNode*)nodes[0]);
    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_IMPLEMENTS_INTERFACE_NAME_NODE)) {
            implementsInterfaceListNode->addInterface((ASTImplementsInterfaceNameNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE)) {
            implementsInterfaceListNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to implements interface list since node list is malformed");
        }
    }

    implementsInterfaceListNode
    ->addInterface(((ASTImplementsInterfaceNameLastNode*)nodes[nodes.size() - 1])->convertToInterfaceName());

    return implementsInterfaceListNode;
}