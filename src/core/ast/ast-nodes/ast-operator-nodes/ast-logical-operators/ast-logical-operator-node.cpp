//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-logical-operator-node.h"

bool ASTLogicalOperatorNode::isAnd() {
    return _lexeme->getToken()->getSymbol()->isAnd();
}

bool ASTLogicalOperatorNode::isOr() {
    return _lexeme->getToken()->getSymbol()->isOr();
}

ASTNodeType ASTLogicalOperatorNode::getNodeType() {
    return AST_LOGICAL_OPERATOR_NODE;
}

std::string ASTLogicalOperatorNode::toString() {
    return "LOGICAL_OPERATOR";
}