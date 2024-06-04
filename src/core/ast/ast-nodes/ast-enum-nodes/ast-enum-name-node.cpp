//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTEnumNameNode::getNodeType() {
    return AST_ENUM_NAME_NODE;
}

std::string ASTEnumNameNode::toString() {
    return "ENUM_NAME";
}
