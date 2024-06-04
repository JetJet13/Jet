//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-break-node.h"

ASTNodeType ASTBreakNode::getNodeType() {
    return AST_BREAK_NODE;
}

std::string ASTBreakNode::toString() {
    return "BREAK";
}
