//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-catch-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTNodeType ASTCatchNode::getNodeType() {
    return AST_CATCH_NODE;
}

std::string ASTCatchNode::toString() {
    return "CATCH";
}