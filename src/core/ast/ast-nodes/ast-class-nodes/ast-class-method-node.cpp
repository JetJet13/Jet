//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-method-node.h"

ASTNodeType ASTClassMethodNameNode::getNodeType() {
    return AST_CLASS_METHOD_NAME_NODE;
}

std::string ASTClassMethodNameNode::toString() {
    return "CLASS_METHOD_NAME";
}