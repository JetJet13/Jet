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

ASTNodeType ASTBinaryOperatorNode::getNodeType() {
    return AST_BINARY_OPERATOR_NODE;
}

std::string ASTBinaryOperatorNode::toString() {
    return "BINARY_OPERATOR";
}

bool ASTSymbolNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTSymbolNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTSymbolNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTSymbolNode::toSourceCode() {
    return this->getLexeme()->getToken()->getSymbol()->toString();
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