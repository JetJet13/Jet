//
// Created by Johny Georges on 2024-02-07.
//

#include "ast-binary-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryOperatorNode::ASTBinaryOperatorNode(Lexeme* lexeme) {
    _lexeme = lexeme;
    _priority = this->determinePriority(lexeme);
}

Lexeme* ASTBinaryOperatorNode::getOperator() {
    return _lexeme;
}

unsigned int ASTBinaryOperatorNode::getPriority() const {
    return _priority;
}

bool ASTBinaryOperatorNode::isHigherOrEqualPriorityThan(ASTBinaryOperatorNode* other) const {
    return _priority <= other->getPriority();
}

bool ASTBinaryOperatorNode::isPlus() {
    return _lexeme->getToken()->getSymbol()->isPlus();
}

bool ASTBinaryOperatorNode::isMinus() {
    return _lexeme->getToken()->getSymbol()->isMinus();
}

bool ASTBinaryOperatorNode::isMultiply() {
    return _lexeme->getToken()->getSymbol()->isStar();
}

bool ASTBinaryOperatorNode::isDivide() {
    return _lexeme->getToken()->getSymbol()->isSlash();
}

bool ASTBinaryOperatorNode::isModulo() {
    return _lexeme->getToken()->getSymbol()->isModulo();
}

bool ASTBinaryOperatorNode::isEqual() {
    return _lexeme->getToken()->getSymbol()->isEqualityOperator();
}

bool ASTBinaryOperatorNode::isNotEqual() {
    return _lexeme->getToken()->getSymbol()->isInequalityOperator();
}

bool ASTBinaryOperatorNode::isGreaterThan() {
    return _lexeme->getToken()->getSymbol()->isGreaterThan();
}

bool ASTBinaryOperatorNode::isLessThan() {
    return _lexeme->getToken()->getSymbol()->isLessThan();
}

bool ASTBinaryOperatorNode::isGreaterThanOrEqual() {
    return _lexeme->getToken()->getSymbol()->isGreaterThanOrEqual();
}

bool ASTBinaryOperatorNode::isLessThanOrEqual() {
    return _lexeme->getToken()->getSymbol()->isLessThanOrEqual();
}

bool ASTBinaryOperatorNode::isArithmetic() {
    return this->isPlus() ||
    this->isMinus() ||
    this->isMultiply() ||
    this->isDivide() ||
    this->isModulo();
}

bool ASTBinaryOperatorNode::isComparator() {
    return this->isEqual() ||
    this->isNotEqual() ||
    this->isLessThan() ||
    this->isLessThanOrEqual() ||
    this->isGreaterThan() ||
    this->isGreaterThanOrEqual();
}

Position* ASTBinaryOperatorNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

Position* ASTBinaryOperatorNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTBinaryOperatorNode::getNodeType() {
    return AST_BINARY_OPERATOR_NODE;
}

std::string ASTBinaryOperatorNode::toString() {
    return "BINARY_OPERATOR";
}

bool ASTBinaryOperatorNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTBinaryOperatorNode*)other;
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}

void ASTBinaryOperatorNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTBinaryOperatorNode::toSourceCode() {
    return this->getOperator()->getToken()->getSymbol()->toString();
}

unsigned int ASTBinaryOperatorNode::determinePriority(Lexeme* lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isSlash() || symbol->isStar()) {
        return 1;
    } else if (symbol->isMinus() || symbol->isPlus()) {
        return 2;
    } else {
        return 10;
    }
}