//
// Created by Johny Georges on 2024-02-20.
//

#include "./ast-unary-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

bool ASTUnaryOperatorNode::isPlus() {
    return _lexeme->getToken()->getSymbol()->isPlus();
}

bool ASTUnaryOperatorNode::isMinus() {
    return _lexeme->getToken()->getSymbol()->isMinus();
}

bool ASTUnaryOperatorNode::isBang() {
    return _lexeme->getToken()->getSymbol()->isBang();
}

ASTNodeType ASTUnaryOperatorNode::getNodeType() {
    return AST_UNARY_OPERATOR_NODE;
}

std::string ASTUnaryOperatorNode::toString() {
    return "UNARY_OPERATOR";
}