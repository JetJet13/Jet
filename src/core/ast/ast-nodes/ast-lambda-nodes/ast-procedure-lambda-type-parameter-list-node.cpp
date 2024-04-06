//
// Created by Johny Georges on 2024-04-06.
//

#include "ast-procedure-lambda-type-parameter-list-node.h"

ASTNodeType ASTProcedureLambdaTypeParameterListNode::getNodeType() {
    return AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE;
}

std::string ASTProcedureLambdaTypeParameterListNode::toString() {
    return "PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST";
}