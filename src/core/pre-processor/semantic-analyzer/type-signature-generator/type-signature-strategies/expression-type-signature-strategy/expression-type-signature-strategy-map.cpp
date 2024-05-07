//
// Created by Johny Georges on 2024-05-06.
//

#include "expression-type-signature-strategy-map.h"

ExpressionTypeSignatureStrategyMap::ExpressionTypeSignatureStrategyMap() {
    _binaryExpressionTypeSignatureStrategy = new BinaryExpressionTypeSignatureStrategy();
}

BinaryExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getBinaryExpressionTypeSignatureStrategy() {
    return this->_binaryExpressionTypeSignatureStrategy;
}