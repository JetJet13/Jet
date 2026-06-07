//
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-end-node.h"

ASTNodeType ASTBlockEndNode::getNodeType() {
    return AST_BLOCK_END_NODE;
}

std::string ASTBlockEndNode::toString() {
    return "BLOCK_END";
}