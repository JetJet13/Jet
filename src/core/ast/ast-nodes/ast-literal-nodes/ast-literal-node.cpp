//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-node.h"

ASTNodeType ASTLiteralNode::getNodeType() {
    return AST_LITERAL_NODE;
}

std::string ASTLiteralNode::toString() {
    return "LITERAL";
}