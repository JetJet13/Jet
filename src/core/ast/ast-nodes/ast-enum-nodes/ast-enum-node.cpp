//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTNodeType ASTEnumNode::getNodeType() {
    return AST_ENUM_NODE;
}

std::string ASTEnumNode::toString() {
    return "ENUM";
}
