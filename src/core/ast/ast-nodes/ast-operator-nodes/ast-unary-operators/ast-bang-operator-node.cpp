//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-bang-operator-node.h"

ASTBangOperatorNode::ASTBangOperatorNode(Lexeme* bangOperator) {
    _bangOperator = bangOperator;
}

ASTNodeType ASTBangOperatorNode::getNodeType() {
    return AST_BANG_OPERATOR_NODE;
}