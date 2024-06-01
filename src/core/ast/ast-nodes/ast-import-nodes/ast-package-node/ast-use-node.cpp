//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTNodeType ASTUseNode::getNodeType() {
    return AST_USE_NODE;
}

std::string ASTUseNode::toString() {
    return "USE";
}