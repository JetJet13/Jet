//
// Created by Johny Georges on 2025-07-09.
//

#include "ast-lambda-type-parameter-list-end-node.h"

ASTNodeType ASTLambdaTypeParameterListEndNode::getNodeType() {
    return AST_LAMBDA_TYPE_PARAMETER_LIST_END_NODE;
}

std::string ASTLambdaTypeParameterListEndNode::toString() {
    return "LAMBDA_TYPE_PARAMETER_LIST_END";
}