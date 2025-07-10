//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-lambda-type-parameter-list-start-node.h"

ASTNodeType ASTLambdaTypeParameterListStartNode::getNodeType() {
    return AST_LAMBDA_TYPE_PARAMETER_LIST_START_NODE;
}

std::string ASTLambdaTypeParameterListStartNode::toString() {
    return "LAMBDA_TYPE_PARAMETER_LIST_START";
}