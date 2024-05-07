//
// Created by Johny Georges on 2024-02-07.
//

#include "ast-binary-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryOperatorNode::ASTBinaryOperatorNode(Lexeme* lexemeOperator) {
    _lexemeOperator = lexemeOperator;
    _priority = this->determinePriority(lexemeOperator);
}

Lexeme* ASTBinaryOperatorNode::getOperator() {
    return _lexemeOperator;
}

bool ASTBinaryOperatorNode::isPlus() {
    return _lexemeOperator->getToken()->getSymbol()->isPlus();
}

bool ASTBinaryOperatorNode::isMinus() {
    return _lexemeOperator->getToken()->getSymbol()->isMinus();
}

bool ASTBinaryOperatorNode::isMultiply() {
    return _lexemeOperator->getToken()->getSymbol()->isStar();
}

bool ASTBinaryOperatorNode::isDivide() {
    return _lexemeOperator->getToken()->getSymbol()->isSlash();
}

bool ASTBinaryOperatorNode::isModulo() {
    return _lexemeOperator->getToken()->getSymbol()->isModulo();
}

bool ASTBinaryOperatorNode::isEqual() {
    return _lexemeOperator->getToken()->getSymbol()->isEqualityOperator();
}

bool ASTBinaryOperatorNode::isNotEqual() {
    return _lexemeOperator->getToken()->getSymbol()->isInequalityOperator();
}

bool ASTBinaryOperatorNode::isGreaterThan() {
    return _lexemeOperator->getToken()->getSymbol()->isGreaterThan();
}

bool ASTBinaryOperatorNode::isLessThan() {
    return _lexemeOperator->getToken()->getSymbol()->isLessThan();
}

bool ASTBinaryOperatorNode::isGreaterThanOrEqual() {
    return _lexemeOperator->getToken()->getSymbol()->isGreaterThanOrEqual();
}

bool ASTBinaryOperatorNode::isLessThanOrEqual() {
    return _lexemeOperator->getToken()->getSymbol()->isLessThanOrEqual();
}

ASTNodeType ASTBinaryOperatorNode::getNodeType() {
    return AST_BINARY_OPERATOR_NODE;
}

std::string ASTBinaryOperatorNode::toString() {
    return "BINARY_OPERATOR - " + _lexemeOperator->toString();
}

bool ASTBinaryOperatorNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTBinaryOperatorNode*)other;
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}

unsigned int ASTBinaryOperatorNode::determinePriority(Lexeme* lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isSlash()) {
        return 1;
    } else if (symbol->isStar()) {
        return 2;
    } else if (symbol->isMinus()) {
        return 3;
    } else if (symbol->isPlus()) {
        return 4;
    } else if (symbol->isModulo()) {
        return 9;
    } else {
        return 10;
    }
}