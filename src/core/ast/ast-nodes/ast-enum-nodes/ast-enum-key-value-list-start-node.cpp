//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-start-node.h"

ASTNodeType ASTEnumKeyValueListStartNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_LIST_START_NODE;
}

std::string ASTEnumKeyValueListStartNode::toString() {
    return "ENUM_KEY_VALUE_LIST_START";
}