//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-start-node.h"

ASTNodeType ASTInterfaceStartNode::getNodeType() {
    return AST_INTERFACE_START_NODE;
}

std::string ASTInterfaceStartNode::toString() {
    return "INTERFACE_START";
}