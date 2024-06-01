//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFunctionParameterListStartNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_LIST_START_NODE;
}

std::string ASTFunctionParameterListStartNode::toString() {
    return "FUNCTION_PARAMETER_LIST_START";
}