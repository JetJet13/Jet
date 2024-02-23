//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-minus-operator-node.h"

ASTMinusOperatorNode::ASTMinusOperatorNode(Lexeme* minusOperator) {
    _minusOperator = minusOperator;
}

ASTNodeType ASTMinusOperatorNode::getNodeType() {
    return AST_MINUS_OPERATOR_NODE;
}