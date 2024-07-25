//
// Created by Johny Georges on 2024-06-15.
//

#include "ir-strategy-map.h"
#include "./literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "./literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "./literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "./literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "./literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "./expression-ir-strategies/literal-expression-ir-strategy/literal-expression-ir-strategy.h"
#include "./expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "./expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "./expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "./expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "./variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
#include "./function-declaration-ir-strategy/function-declaration-ir-strategy.h"
#include "./function-parameter-list-ir-strategy/function-parameter-list-ir-strategy.h"
#include "./function-return-expression-ir-strategy/function-return-expression-ir-strategy.h"
#include "./procedure-declaration-ir-strategy/procedure-declaration-ir-strategy.h"
#include "./enum-declaration-ir-strategy/enum-declaration-ir-strategy.h"
#include "./type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/literal-type-signature-ir-strategy/literal-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-type-signature-ir-strategy/class-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/enum-type-signature-ir-strategy/enum-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/function-type-signature-ir-strategy/function-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/lambda-type-signature-ir-strategy/lambda-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/procedure-type-signature-ir-strategy/procedure-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-list-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/struct-type-signature-ir-strategy/struct-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/tuple-type-signature-ir-strategy/tuple-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/enum-access-type-signature-ir-strategy/enum-access-type-signature-ir-strategy.h"


IRStrategyMap::IRStrategyMap() {
    _intLiteralIRStrategy = new IntLiteralIRStrategy();
    _floatLiteralIRStrategy = new FloatLiteralIRStrategy();
    _charLiteralIRStrategy = new CharLiteralIRStrategy();
    _stringLiteralIRStrategy = new StringLiteralIRStrategy();
    _boolLiteralIRStrategy = new BoolLiteralIRStrategy();
    _literalExpressionIRStrategy = new LiteralExpressionIRStrategy();
    _binaryExpressionIRStrategy = new BinaryExpressionIRStrategy();
    _logicalExpressionIRStrategy = new LogicalExpressionIRStrategy();
    _arrayExpressionIRStrategy = new ArrayExpressionIRStrategy();
    _structExpressionIRStrategy = new StructExpressionIRStrategy();
    _arrayAccessExpressionIRStrategy = new ArrayAccessExpressionIRStrategy();
    _unaryExpressionIRStrategy = new UnaryExpressionIRStrategy();
    _tupleExpressionIRStrategy = new TupleExpressionIRStrategy();
    _identifierExpressionIRStrategy = new IdentifierExpressionIRStrategy();
    _variableDeclarationIRStrategy = new VariableDeclarationIRStrategy();
    _functionDeclarationIRStrategy = new FunctionDeclarationIRStrategy();
    _functionParameterListIRStrategy = new FunctionParameterListIRStrategy();
    _functionReturnExpressionIRStrategy = new FunctionReturnExpressionIRStrategy();
    _procedureDeclarationIRStrategy = new ProcedureDeclarationIRStrategy();
    _enumDeclarationIRStrategy = new EnumDeclarationIRStrategy();
    _objectAccessExpressionIRStrategy = new ObjectAccessExpressionIRStrategy();

    _arrayTypeSignatureIRStrategy = new ArrayTypeSignatureIRStrategy();
    _literalTypeSignatureIRStrategy = new LiteralTypeSignatureIRStrategy();
    _classTypeSignatureIRStrategy = new ClassTypeSignatureIRStrategy();
    _enumTypeSignatureIRStrategy = new EnumTypeSignatureIRStrategy();
    _functionTypeSignatureIRStrategy = new FunctionTypeSignatureIRStrategy();
    _lambdaTypeSignatureIRStrategy = new LambdaTypeSignatureIRStrategy();
    _procedureTypeSignatureIRStrategy = new ProcedureTypeSignatureIRStrategy();
    _parameterListTypeSignatureIRStrategy = new ParameterListTypeSignatureIRStrategy();
    _parameterTypeSignatureIRStrategy = new ParameterTypeSignatureIRStrategy();
    _structTypeSignatureIRStrategy = new StructTypeSignatureIRStrategy();
    _tupleTypeSignatureIRStrategy = new TupleTypeSignatureIRStrategy();
    _enumAccessTypeSignatureIRStrategy = new EnumAccessTypeSignatureIRStrategy();
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

LiteralExpressionIRStrategy* IRStrategyMap::getLiteralExpressionIRStrategy() {
    return _literalExpressionIRStrategy;
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

ArrayAccessExpressionIRStrategy* IRStrategyMap::getArrayAccessExpressionIRStrategy() {
    return _arrayAccessExpressionIRStrategy;
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

IdentifierExpressionIRStrategy* IRStrategyMap::getIdentifierExpressionIRStrategy() {
    return _identifierExpressionIRStrategy;
}

VariableDeclarationIRStrategy* IRStrategyMap::getVariableDeclarationIRStrategy() {
    return _variableDeclarationIRStrategy;
}

FunctionDeclarationIRStrategy* IRStrategyMap::getFunctionDeclarationIRStrategy() {
    return _functionDeclarationIRStrategy;
}

FunctionParameterListIRStrategy* IRStrategyMap::getFunctionParameterListIRStrategy() {
    return _functionParameterListIRStrategy;
}

FunctionReturnExpressionIRStrategy* IRStrategyMap::getFunctionReturnExpressionIRStrategy() {
    return _functionReturnExpressionIRStrategy;
}

ProcedureDeclarationIRStrategy* IRStrategyMap::getProcedureDeclarationIRStrategy() {
    return _procedureDeclarationIRStrategy;
}

EnumDeclarationIRStrategy* IRStrategyMap::getEnumDeclarationIRStrategy() {
    return _enumDeclarationIRStrategy;
}

ObjectAccessExpressionIRStrategy* IRStrategyMap::getObjectAccessExpressionIRStrategy() {
    return _objectAccessExpressionIRStrategy;
}

ArrayTypeSignatureIRStrategy* IRStrategyMap::getArrayTypeSignatureIRStrategy() {
    return _arrayTypeSignatureIRStrategy;
}

LiteralTypeSignatureIRStrategy* IRStrategyMap::getLiteralTypeSignatureIRStrategy() {
    return _literalTypeSignatureIRStrategy;
}

ClassTypeSignatureIRStrategy* IRStrategyMap::getClassTypeSignatureIRStrategy() {
    return _classTypeSignatureIRStrategy;
}

EnumTypeSignatureIRStrategy* IRStrategyMap::getEnumTypeSignatureIRStrategy() {
    return _enumTypeSignatureIRStrategy;
}

FunctionTypeSignatureIRStrategy* IRStrategyMap::getFunctionTypeSignatureIRStrategy() {
    return _functionTypeSignatureIRStrategy;
}

LambdaTypeSignatureIRStrategy* IRStrategyMap::getLambdaTypeSignatureIRStrategy() {
    return _lambdaTypeSignatureIRStrategy;
}

ProcedureTypeSignatureIRStrategy* IRStrategyMap::getProcedureTypeSignatureIRStrategy() {
    return _procedureTypeSignatureIRStrategy;
}

ParameterListTypeSignatureIRStrategy* IRStrategyMap::getParameterListTypeSignatureIRStrategy() {
    return _parameterListTypeSignatureIRStrategy;
}

ParameterTypeSignatureIRStrategy* IRStrategyMap::getParameterTypeSignatureIRStrategy() {
    return _parameterTypeSignatureIRStrategy;
}

StructTypeSignatureIRStrategy* IRStrategyMap::getStructTypeSignatureIRStrategy() {
    return _structTypeSignatureIRStrategy;
}

TupleTypeSignatureIRStrategy* IRStrategyMap::getTupleTypeSignatureIRStrategy() {
    return _tupleTypeSignatureIRStrategy;
}

EnumAccessTypeSignatureIRStrategy* IRStrategyMap::getEnumAccessTypeSignatureIRStrategy() {
    return _enumAccessTypeSignatureIRStrategy;
}