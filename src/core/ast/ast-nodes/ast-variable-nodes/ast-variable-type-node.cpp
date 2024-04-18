//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-type-node.h"

ASTNodeType ASTVariableTypeNode::getNodeType() {
    return AST_VARIABLE_TYPE_NODE;
}

std::string ASTVariableTypeNode::toString() {
    return "VARIABLE_TYPE";
}
