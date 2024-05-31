//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-function-call-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTNodeType ASTFunctionCallNode::getNodeType() {
    return AST_FUNCTION_CALL_NODE;
}

std::string ASTFunctionCallNode::toString() {
    return "FUNCTION_CALL";
}

std::string ASTFunctionCallNode::toSourceCode() {
    Logger::log(this->getId());
}
