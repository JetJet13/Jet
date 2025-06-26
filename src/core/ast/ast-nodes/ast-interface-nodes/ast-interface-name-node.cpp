//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-name-node.h"

ASTNodeType ASTInterfaceNameNode::getNodeType() {
    return AST_INTERFACE_NAME_NODE;
}

std::string ASTInterfaceNameNode::toString() {
    return "INTERFACE_NAME";
}

std::string ASTInterfaceNameNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}