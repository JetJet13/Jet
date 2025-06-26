//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-node.h"

ASTNodeType ASTInterfaceNode::getNodeType() {
    return AST_INTERFACE_NODE;
}

std::string ASTInterfaceNode::toString() {
    return "INTERFACE";
}