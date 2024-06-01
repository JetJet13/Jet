//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-as-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTAsNode::getNodeType() {
    return AST_AS_NODE;
}

std::string ASTAsNode::toString() {
    return "AS";
}
