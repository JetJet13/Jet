//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-keyword-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTArrayTypeKeywordNode::getNodeType() {
    return AST_ARRAY_TYPE_KEYWORD_NODE;
}

std::string ASTArrayTypeKeywordNode::toString() {
    return "ARRAY_TYPE_KEYWORD";
}
