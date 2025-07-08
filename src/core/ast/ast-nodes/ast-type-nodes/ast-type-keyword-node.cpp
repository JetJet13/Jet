//
// Created by Johny Georges on 2025-07-07.
//

#include "ast-type-keyword-node.h"

ASTNodeType ASTTypeKeywordNode::getNodeType() {
    return AST_TYPE_KEYWORD_NODE;
}

std::string ASTTypeKeywordNode::toString() {
    return "TYPE_KEYWORD";
}