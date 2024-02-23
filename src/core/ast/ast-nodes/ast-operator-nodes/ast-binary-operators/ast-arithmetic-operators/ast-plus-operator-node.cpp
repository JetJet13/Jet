//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-plus-operator-node.h"

ASTPlusOperatorNode::ASTPlusOperatorNode(Lexeme* plusOperator) {
    _plusOperator = plusOperator;
}

ASTNodeType ASTPlusOperatorNode::getNodeType() {
    return AST_PLUS_OPERATOR_NODE;
}