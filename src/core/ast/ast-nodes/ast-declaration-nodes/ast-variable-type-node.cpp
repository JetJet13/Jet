//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-type-node.h"

ASTVariableTypeNode::ASTVariableTypeNode(Lexeme* varTypeQualifier) {
    _varTypeQualifier = varTypeQualifier;
}

ASTNodeType ASTVariableTypeNode::getNodeType() {
    return AST_VARIABLE_TYPE_NODE;
}
