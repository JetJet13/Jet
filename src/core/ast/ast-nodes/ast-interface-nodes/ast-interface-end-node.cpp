//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-end-node.h"

ASTNodeType ASTInterfaceEndNode::getNodeType() {
    return AST_INTERFACE_END_NODE;
}

std::string ASTInterfaceEndNode::toString() {
    return "INTERFACE_END";
}