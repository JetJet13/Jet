//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-unary-minus-operator.h"

ASTUnaryMinusOperatorNode::ASTUnaryMinusOperatorNode(Lexeme* minusOperator) {
    _minusOperator = minusOperator;
}

ASTNodeType ASTUnaryMinusOperatorNode::getNodeType() {
    return AST_UNARY_MINUS_OPERATOR_NODE;
}
