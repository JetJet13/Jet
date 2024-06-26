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
#include "./expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "./expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "./identifier-ir-strategy/identifier-ir-strategy.h"
#include "./variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
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
    _structExpressionIRStrategy = new StructExpressionIRStrategy();
    _arrayTypeSignatureIRStrategy = new ArrayTypeSignatureIRStrategy();
    _unaryExpressionIRStrategy = new UnaryExpressionIRStrategy();
    _tupleExpressionIRStrategy = new TupleExpressionIRStrategy();
    _identifierIRStrategy = new IdentifierIRStrategy();
    _variableDeclarationIRStrategy = new VariableDeclarationIRStrategy();
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

StructExpressionIRStrategy* IRStrategyMap::getStructExpressionIRStrategy() {
    return _structExpressionIRStrategy;
}

UnaryExpressionIRStrategy* IRStrategyMap::getUnaryExpressionIRStrategy() {
    return _unaryExpressionIRStrategy;
}

TupleExpressionIRStrategy* IRStrategyMap::getTupleExpressionIRStrategy() {
    return _tupleExpressionIRStrategy;
}

IdentifierIRStrategy* IRStrategyMap::getIdentifierIRStrategy() {
    return _identifierIRStrategy;
}

VariableDeclarationIRStrategy* IRStrategyMap::getVariableDeclarationIRStrategy() {
    return _variableDeclarationIRStrategy;
}

ArrayTypeSignatureIRStrategy* IRStrategyMap::getArrayTypeSignatureIRStrategy() {
    return _arrayTypeSignatureIRStrategy;
}