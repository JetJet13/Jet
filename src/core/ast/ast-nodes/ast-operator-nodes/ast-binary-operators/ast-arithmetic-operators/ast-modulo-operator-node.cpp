//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-modulo-operator-node.h"

ASTModuloOperatorNode::ASTModuloOperatorNode(Lexeme* moduloOperator) {
    _moduloOperator = moduloOperator;
}

ASTNodeType ASTModuloOperatorNode::getNodeType() {
    return AST_MODULO_OPERATOR_NODE;
}

std::string ASTModuloOperatorNode::toString() {
    return "MODULO_OPERATOR";
}