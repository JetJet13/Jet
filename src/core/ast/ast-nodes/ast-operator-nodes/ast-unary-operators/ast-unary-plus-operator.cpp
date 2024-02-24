//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-unary-plus-operator.h"

ASTUnaryPlusOperatorNode::ASTUnaryPlusOperatorNode(Lexeme* plusOperator) {
    _plusOperator = plusOperator;
}

ASTNodeType ASTUnaryPlusOperatorNode::getNodeType() {
    return AST_UNARY_PLUS_OPERATOR_NODE;
}

std::string ASTUnaryPlusOperatorNode::toString() {
    return "UNARY_PLUS_OPERATOR";
}