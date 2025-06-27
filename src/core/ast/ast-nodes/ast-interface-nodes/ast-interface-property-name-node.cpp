//
// Created by Johny Georges on 2025-06-26.
//

#include "ast-interface-property-name-node.h"

ASTNodeType ASTInterfacePropertyNameNode::getNodeType() {
    return AST_INTERFACE_PROPERTY_NAME_NODE;
}

std::string ASTInterfacePropertyNameNode::toString() {
    return "INTERFACE_PROPERTY_NAME";
}
