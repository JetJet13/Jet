//
// Created by Johny Georges on 2025-07-07.
//

#include "ast-type-name-node.h"

ASTNodeType ASTTypeNameNode::getNodeType() {
    return AST_TYPE_NAME_NODE;
}

std::string ASTTypeNameNode::toString() {
    return "TYPE_NAME";
}

std::string ASTTypeNameNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}