//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-string-literal-node.h"

ASTNodeType ASTStringLiteralNode::getNodeType() {
    return AST_STRING_LITERAL_NODE;
}

std::string ASTStringLiteralNode::toString() {
    return "STRING_LITERAL";
}
