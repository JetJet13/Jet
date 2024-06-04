//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-catch-error-variable-node.h"
#include "../../../../../shared/utils/logger/logger.h"


ASTNodeType ASTCatchErrorVariableNode::getNodeType() {
    return AST_CATCH_ERROR_VARIABLE_NODE;
}

std::string ASTCatchErrorVariableNode::toString() {
    return "CATCH_ERROR_VARIABLE";
}