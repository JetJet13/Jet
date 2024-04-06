//
// Created by Johny Georges on 2024-04-06.
//

#include "ast-function-lambda-type-parameter-list-node.h"

ASTNodeType ASTFunctionLambdaTypeParameterListNode::getNodeType() {
    return AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTFunctionLambdaTypeParameterListNode::toString() {
    return "FUNCTION_LAMBDA_TYPE_PARAMETER_LIST";
}