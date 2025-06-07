//
// Created by Johny Georges on 2025-06-07.
//

#include "ast-concat-node.h"

ASTNodeType ASTConcatNode::getNodeType() {
    return AST_CONCAT_NODE;
}

std::string ASTConcatNode::toString() {
    return "CONCAT";
}