//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-fat-arrow-node.h"

ASTNodeType ASTLambdaFatArrowNode::getNodeType() {
    return AST_LAMBDA_FAT_ARROW_NODE;
}

std::string ASTLambdaFatArrowNode::toString() {
    return "LAMBDA_FAT_ARROW";
}