//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-greater-than-operator-node.h"

ASTGreaterThanOperatorNode::ASTGreaterThanOperatorNode(Lexeme *lexeme) {
    _greaterThan = lexeme;
}

ASTNodeType ASTGreaterThanOperatorNode::getNodeType() {
    return AST_GREATER_THAN_OPERATOR_NODE;
}