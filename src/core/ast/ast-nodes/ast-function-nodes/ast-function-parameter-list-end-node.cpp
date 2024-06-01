//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFunctionParameterListEndNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_LIST_END_NODE;
}

std::string ASTFunctionParameterListEndNode::toString() {
    return "FUNCTION_PARAMETER_LIST_END";
}
