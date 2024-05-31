//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-parameter-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTTypeParameterListStartNode::getNodeType() {
    return AST_TYPE_PARAMETER_LIST_START_NODE;
}

std::string ASTTypeParameterListStartNode::toString() {
    return "TYPE_PARAMETER_LIST_START";
}