//
// Created by Johny Georges on 2025-07-23.
//

#include "ast-range-node.h"

ASTNodeType ASTRangeNode::getNodeType() {
    return AST_RANGE_NODE;
}

std::string ASTRangeNode::toString() {
    return "RANGE";
}