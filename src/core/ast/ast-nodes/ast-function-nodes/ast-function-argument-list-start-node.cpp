//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFunctionArgumentListStartNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_LIST_START_NODE;
}

std::string ASTFunctionArgumentListStartNode::toString() {
    return "FUNCTION_ARGUMENT_LIST_START";
}