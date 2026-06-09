//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-expression-fat-arrow-node.h"

ASTNodeType ASTLambdaExpressionFatArrowNode::getNodeType() {
    return AST_LAMBDA_EXPRESSION_FAT_ARROW_NODE;
}

std::string ASTLambdaExpressionFatArrowNode::toString() {
    return "LAMBDA_EXPRESSION_FAT_ARROW";
}