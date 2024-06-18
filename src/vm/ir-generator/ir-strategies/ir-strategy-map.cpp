//
// Created by Johny Georges on 2024-06-15.
//

#include "ir-strategy-map.h"
#include "./literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "./literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "./literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "./literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "./literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "./expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "./expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "./type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"

IRStrategyMap::IRStrategyMap() {
    _intLiteralIRStrategy = new IntLiteralIRStrategy();
    _floatLiteralIRStrategy = new FloatLiteralIRStrategy();
    _charLiteralIRStrategy = new CharLiteralIRStrategy();
    _stringLiteralIRStrategy = new StringLiteralIRStrategy();
    _boolLiteralIRStrategy = new BoolLiteralIRStrategy();
    _binaryExpressionIRStrategy = new BinaryExpressionIRStrategy();
    _logicalExpressionIRStrategy = new LogicalExpressionIRStrategy();
    _arrayExpressionIRStrategy = new ArrayExpressionIRStrategy();
    _arrayTypeSignatureIRStrategy = new ArrayTypeSignatureIRStrategy();
}

IntLiteralIRStrategy* IRStrategyMap::getIntLiteralIRStrategy() {
    return _intLiteralIRStrategy;
}

FloatLiteralIRStrategy* IRStrategyMap::getFloatLiteralIRStrategy() {
    return _floatLiteralIRStrategy;
}

CharLiteralIRStrategy* IRStrategyMap::getCharLiteralIRStrategy() {
    return _charLiteralIRStrategy;
}

StringLiteralIRStrategy* IRStrategyMap::getStringLiteralIRStrategy() {
    return _stringLiteralIRStrategy;
}

BoolLiteralIRStrategy* IRStrategyMap::getBoolLiteralIRStrategy() {
    return _boolLiteralIRStrategy;
}

BinaryExpressionIRStrategy* IRStrategyMap::getBinaryExpressionIRStrategy() {
    return _binaryExpressionIRStrategy;
}

LogicalExpressionIRStrategy* IRStrategyMap::getLogicalExpressionIRStrategy() {
    return _logicalExpressionIRStrategy;
}

ArrayExpressionIRStrategy* IRStrategyMap::getArrayExpressionIRStrategy() {
    return _arrayExpressionIRStrategy;
}

ArrayTypeSignatureIRStrategy* IRStrategyMap::getArrayTypeSignatureIRStrategy() {
    return _arrayTypeSignatureIRStrategy;
}