//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTElseNode::getNodeType() {
    return AST_ELSE_NODE;
}

std::string ASTElseNode::toString() {
    return "ELSE";
}