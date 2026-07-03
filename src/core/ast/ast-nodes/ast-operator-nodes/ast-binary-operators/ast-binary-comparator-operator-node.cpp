//
// Created by Johny Georges on 2026-03-02.
//

#include "ast-binary-comparator-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryComparatorOperatorNode::ASTBinaryComparatorOperatorNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTBinaryComparatorOperatorNode::getOperator() {
    return _lexeme;
}

bool ASTBinaryComparatorOperatorNode::isEqual() {
    return _lexeme->getToken()->getSymbol()->isEqualityOperator();
}

bool ASTBinaryComparatorOperatorNode::isNotEqual() {
    return _lexeme->getToken()->getSymbol()->isInequalityOperator();
}

bool ASTBinaryComparatorOperatorNode::isGreaterThan() {
    return _lexeme->getToken()->getSymbol()->isGreaterThan();
}

bool ASTBinaryComparatorOperatorNode::isLessThan() {
    return _lexeme->getToken()->getSymbol()->isLessThan();
}

bool ASTBinaryComparatorOperatorNode::isGreaterThanOrEqual() {
    return _lexeme->getToken()->getSymbol()->isGreaterThanOrEqual();
}

bool ASTBinaryComparatorOperatorNode::isLessThanOrEqual() {
    return _lexeme->getToken()->getSymbol()->isLessThanOrEqual();
}

Position* ASTBinaryComparatorOperatorNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

Position* ASTBinaryComparatorOperatorNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTBinaryComparatorOperatorNode::getNodeType() {
    return AST_BINARY_COMPARATOR_OPERATOR_NODE;
}

std::string ASTBinaryComparatorOperatorNode::toString() {
    return "BINARY_COMPARATOR_OPERATOR";
}

bool ASTBinaryComparatorOperatorNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTBinaryComparatorOperatorNode*)other;
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}

void ASTBinaryComparatorOperatorNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTBinaryComparatorOperatorNode::toSourceCode() {
    return this->getOperator()->getToken()->getSymbol()->toString();
}