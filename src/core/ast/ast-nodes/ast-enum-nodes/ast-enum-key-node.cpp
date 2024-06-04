//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTEnumKeyNode::getNodeType() {
    return AST_ENUM_KEY_NODE;
}

std::string ASTEnumKeyNode::toString() {
    return "ENUM_KEY";
}
