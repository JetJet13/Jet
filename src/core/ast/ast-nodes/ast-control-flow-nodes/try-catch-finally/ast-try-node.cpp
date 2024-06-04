//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-try-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTNodeType ASTTryNode::getNodeType() {
    return AST_TRY_NODE;
}

std::string ASTTryNode::toString() {
    return "TRY";
}