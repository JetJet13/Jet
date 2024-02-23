//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-star-operator-node.h"

ASTStarOperatorNode::ASTStarOperatorNode(Lexeme* starOperator) {
    _starOperator = starOperator;
}

ASTNodeType ASTStarOperatorNode::getNodeType() {
    return AST_STAR_OPERATOR_NODE;
}