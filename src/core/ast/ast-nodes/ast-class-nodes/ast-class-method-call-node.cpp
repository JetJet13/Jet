//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-method-call-node.h"

ASTNodeType ASTClassMethodCallNode::getNodeType() {
    return AST_CLASS_METHOD_CALL_NODE;
}

std::string ASTClassMethodCallNode::toString() {
    return "CLASS_METHOD_CALL";
}