//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-class-node.h"

ASTNodeType ASTClassNode::getNodeType() {
    return AST_CLASS_NODE;
}

std::string ASTClassNode::toString() {
    return "CLASS";
}