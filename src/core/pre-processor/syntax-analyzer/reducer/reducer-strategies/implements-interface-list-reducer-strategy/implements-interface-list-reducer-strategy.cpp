//
// Created by Johny Georges on 2025-07-05.
//

#include "implements-interface-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-list-node.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-name-last-node.h"

std::shared_ptr<ASTNode> ImplementsInterfaceListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto implementsInterfaceListNode = std::make_shared<ASTImplementsInterfaceListNode>(std::dynamic_pointer_cast<ASTImplementsNode>(nodes[0]));
    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_IMPLEMENTS_INTERFACE_NAME_NODE)) {
            implementsInterfaceListNode->addInterface(std::dynamic_pointer_cast<ASTImplementsInterfaceNameNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE)) {
            implementsInterfaceListNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to implements interface list since node list is malformed");
        }
    }

    implementsInterfaceListNode
    ->addInterface((std::dynamic_pointer_cast<ASTImplementsInterfaceNameLastNode>(nodes[nodes.size() - 1]))->convertToInterfaceName());

    return implementsInterfaceListNode;
}