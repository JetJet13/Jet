//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-from-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFromNode::getNodeType() {
    return AST_FROM_NODE;
}

std::string ASTFromNode::toString() {
    return "FROM";
}