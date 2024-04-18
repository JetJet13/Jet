//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-constructor-node.h"

ASTNodeType ASTConstructorNode::getNodeType() {
    return AST_CONSTRUCTOR_NODE;
}

std::string ASTConstructorNode::toString() {
    return "CONSTRUCTOR";
}