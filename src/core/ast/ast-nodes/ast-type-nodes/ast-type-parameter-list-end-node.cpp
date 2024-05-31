//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-parameter-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTTypeParameterListEndNode::getNodeType() {
    return AST_TYPE_PARAMETER_LIST_END_NODE;
}

std::string ASTTypeParameterListEndNode::toString() {
    return "TYPE_PARAMETER_LIST_END";
}