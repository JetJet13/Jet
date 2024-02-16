//
// Created by Johny Georges on 2024-02-07.
//

#include "ast-binary-operator-node.h"

ASTBinaryOperatorNode::ASTBinaryOperatorNode(Lexeme* binaryOperator) {
    _binaryOperator = binaryOperator;
}

ASTNodeType ASTBinaryOperatorNode::getNodeType() {
    return AST_BINARY_OPERATOR_NODE;
}