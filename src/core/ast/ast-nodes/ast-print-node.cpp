//
// Created by Johny Georges on 2025-07-21.
//

#include "ast-print-node.h"

ASTNodeType ASTPrintNode::getNodeType() {
    return AST_PRINT_NODE;
}

std::string ASTPrintNode::toString() {
    return "PRINT";
}