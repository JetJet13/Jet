//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTEnumKeyValueListEndNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_LIST_END_NODE;
}

std::string ASTEnumKeyValueListEndNode::toString() {
    return "ENUM_KEY_VALUE_LIST_END";
}
