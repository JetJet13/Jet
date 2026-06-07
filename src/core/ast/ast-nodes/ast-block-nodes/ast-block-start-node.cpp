//
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-start-node.h"

ASTNodeType ASTBlockStartNode::getNodeType() {
    return AST_BLOCK_START_NODE;
}

std::string ASTBlockStartNode::toString() {
    return "BLOCK_START";
}