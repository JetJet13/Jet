//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-function-name-node.h"

ASTNodeType ASTFunctionNameNode::getNodeType() {
    return AST_FUNCTION_NAME_NODE;
}

std::string ASTFunctionNameNode::toString() {
    return "FUNCTION_NAME";
}

std::string ASTFunctionNameNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}