//
// Created by Johny Georges on 2024-02-07.
//

#include "ast-binary-arithmetic-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryArithmeticOperatorNode::ASTBinaryArithmeticOperatorNode(Lexeme* lexeme) {
    _lexeme = lexeme;
    _priority = this->determinePriority(lexeme);
}

Lexeme* ASTBinaryArithmeticOperatorNode::getOperator() {
    return _lexeme;
}

unsigned int ASTBinaryArithmeticOperatorNode::getPriority() const {
    return _priority;
}

bool ASTBinaryArithmeticOperatorNode::isHigherOrEqualPriorityThan(ASTBinaryArithmeticOperatorNode* other) const {
    return _priority <= other->getPriority();
}

bool ASTBinaryArithmeticOperatorNode::isPlus() {
    return _lexeme->getToken()->getSymbol()->isPlus();
}

bool ASTBinaryArithmeticOperatorNode::isMinus() {
    return _lexeme->getToken()->getSymbol()->isMinus();
}

bool ASTBinaryArithmeticOperatorNode::isMultiply() {
    return _lexeme->getToken()->getSymbol()->isStar();
}

bool ASTBinaryArithmeticOperatorNode::isDivide() {
    return _lexeme->getToken()->getSymbol()->isSlash();
}

bool ASTBinaryArithmeticOperatorNode::isModulo() {
    return _lexeme->getToken()->getSymbol()->isModulo();
}

Position* ASTBinaryArithmeticOperatorNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

Position* ASTBinaryArithmeticOperatorNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTBinaryArithmeticOperatorNode::getNodeType() {
    return AST_BINARY_ARITHMETIC_OPERATOR_NODE;
}

std::string ASTBinaryArithmeticOperatorNode::toString() {
    return "BINARY_ARITHMETIC_OPERATOR";
}

bool ASTBinaryArithmeticOperatorNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTBinaryArithmeticOperatorNode*)other;
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}

void ASTBinaryArithmeticOperatorNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTBinaryArithmeticOperatorNode::toSourceCode() {
    return this->getOperator()->getToken()->getSymbol()->toString();
}

unsigned int ASTBinaryArithmeticOperatorNode::determinePriority(Lexeme* lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isSlash() || symbol->isStar()) {
        return 1;
    } else if (symbol->isMinus() || symbol->isPlus()) {
        return 2;
    } else {
        return 10;
    }
}