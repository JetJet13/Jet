//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-while-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTWhileNode::getNodeType() {
    return AST_WHILE_NODE;
}

std::string ASTWhileNode::toString() {
    return "WHILE";
}
