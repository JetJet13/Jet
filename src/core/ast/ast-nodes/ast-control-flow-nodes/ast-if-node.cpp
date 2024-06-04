//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-if-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTIfNode::getNodeType() {
    return AST_IF_NODE;
}

std::string ASTIfNode::toString() {
    return "IF";
}