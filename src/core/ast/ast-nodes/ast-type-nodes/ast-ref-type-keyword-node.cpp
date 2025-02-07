//
// Created by Johny Georges on 2025-02-07.
//

#include "ast-ref-type-keyword-node.h"

ASTNodeType ASTRefTypeKeywordNode::getNodeType() {
    return AST_REF_TYPE_KEYWORD_NODE;
}

std::string ASTRefTypeKeywordNode::toString() {
    return "REF_TYPE_KEYWORD";
}