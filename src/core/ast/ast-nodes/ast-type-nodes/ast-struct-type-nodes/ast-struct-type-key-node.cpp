//
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-key-node.h"

ASTNodeType ASTStructTypeKeyNode::getNodeType() {
    return AST_STRUCT_TYPE_KEY_NODE;
}

std::string ASTStructTypeKeyNode::toString() {
    return "STRUCT_TYPE_KEY";
}

std::string ASTStructTypeKeyNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}