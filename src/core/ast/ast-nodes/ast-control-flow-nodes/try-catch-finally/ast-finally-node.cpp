//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-finally-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFinallyNode::getNodeType() {
    return AST_FINALLY_NODE;
}

std::string ASTFinallyNode::toString() {
    return "FINALLY";
}