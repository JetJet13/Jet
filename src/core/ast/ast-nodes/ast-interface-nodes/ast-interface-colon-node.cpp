//
// Created by Johny Georges on 2025-06-26.
//

#include "ast-interface-colon-node.h"

ASTNodeType ASTInterfaceColonNode::getNodeType() {
    return AST_INTERFACE_COLON_NODE;
}

std::string ASTInterfaceColonNode::toString() {
    return "INTERFACE_COLON";
}