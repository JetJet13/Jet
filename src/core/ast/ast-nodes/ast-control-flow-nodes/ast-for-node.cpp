//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTForNode::getNodeType() {
    return AST_FOR_NODE;
}

std::string ASTForNode::toString() {
    return "FOR";
}