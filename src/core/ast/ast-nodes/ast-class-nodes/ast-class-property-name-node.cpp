//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-name-node.h"

ASTNodeType ASTClassPropertyNameNode::getNodeType() {
    return AST_CLASS_PROPERTY_NAME_NODE;
}

std::string ASTClassPropertyNameNode::toString() {
    return "CLASS_PROPERTY_NAME";
}