//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTFunctionNode::getNodeType() {
    return AST_FUNCTION_NODE;
}

std::string ASTFunctionNode::toString() {
    return "FUNCTION";
}