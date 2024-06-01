//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFunctionArgumentListEndNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_LIST_END_NODE;
}

std::string ASTFunctionArgumentListEndNode::toString() {
    return "FUNCTION_ARGUMENT_LIST_END";
}