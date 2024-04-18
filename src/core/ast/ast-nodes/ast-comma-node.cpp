//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-comma-node.h"

ASTNodeType ASTCommaNode::getNodeType() {
    return AST_COMMA_NODE;
}

std::string ASTCommaNode::toString() {
    return "COMMA";
}
