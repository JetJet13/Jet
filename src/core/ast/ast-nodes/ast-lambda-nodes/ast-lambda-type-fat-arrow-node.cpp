//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-type-fat-arrow-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTLambdaTypeFatArrowNode::getNodeType() {
    return AST_LAMBDA_TYPE_FAT_ARROW_NODE;
}

std::string ASTLambdaTypeFatArrowNode::toString() {
    return "LAMBDA_TYPE_FAT_ARROW";
}
