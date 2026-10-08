//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-lambda-arrow-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTLambdaArrowNode::getNodeType() {
    return AST_LAMBDA_ARROW_NODE;
}

std::string ASTLambdaArrowNode::toString() {
    return "LAMBDA_ARROW";
}
