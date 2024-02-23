//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-equality-operator-node.h"

ASTEqualityOperatorNode::ASTEqualityOperatorNode(Lexeme *lexeme) {
    _equality = lexeme;
}

ASTNodeType ASTEqualityOperatorNode::getNodeType() {
    return AST_EQUALITY_OPERATOR_NODE;
}