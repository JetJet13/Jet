//
// Created by Johny Georges on 2025-07-05.
//

#include "ast-implements-interface-name-node.h"

ASTNodeType ASTImplementsInterfaceNameNode::getNodeType() {
    return AST_IMPLEMENTS_INTERFACE_NAME_NODE;
}

std::string ASTImplementsInterfaceNameNode::toString() {
    return "IMPLEMENTS_INTERFACE_NAME";
}

std::string ASTImplementsInterfaceNameNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}