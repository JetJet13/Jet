//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-return-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFunctionReturnNode::getNodeType() {
    return AST_FUNCTION_RETURN_NODE;
}

std::string ASTFunctionReturnNode::toString() {
    return "FUNCTION_RETURN_NODE";
}
