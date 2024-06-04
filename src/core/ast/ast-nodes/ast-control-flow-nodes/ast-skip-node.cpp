//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-skip-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTSkipNode::getNodeType() {
    return AST_SKIP_NODE;
}

std::string ASTSkipNode::toString() {
    return "SKIP";
}