//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-map.h"
#include "type-type-signature-strategy/type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/primitive-type-type-signature-strategy/primitive-type-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-expression-type-signature-strategy/array-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/binary-expression-type-signature-strategy/binary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-method-invocation-expression-type-signature-strategy/class-method-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-property-expression-type-signature-strategy/class-property-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/curry-expression-type-signature-strategy/curry-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-invocation-expression-type-signature-strategy/function-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-return-expression-type-signature-strategy/function-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/identifier-expression-type-signature-strategy/identifier-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-expression-type-signature-strategy/lambda-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-return-expression-type-signature-strategy/lambda-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/literal-expression-type-signature-strategy/literal-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/lambda-type-type-signature-strategy/lambda-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/this-type-type-signature-strategy/this-type-type-signature-strategy.h"


TypeSignatureStrategyMap::TypeSignatureStrategyMap() {
    _arrayAccessExpressionTypeSignatureStrategy = new ArrayAccessExpressionTypeSignatureStrategy();
    _arrayExpressionTypeSignatureStrategy = new ArrayExpressionTypeSignatureStrategy();
    _binaryExpressionTypeSignatureStrategy = new BinaryExpressionTypeSignatureStrategy();
    _logicalExpressionTypeSignatureStrategy = new LogicalExpressionTypeSignatureStrategy();
    _classMethodInvocationExpressionTypeSignatureStrategy = new ClassMethodInvocationExpressionTypeSignatureStrategy();
    _classPropertyAccessExpressionTypeSignatureStrategy = new ClassPropertyAccessExpressionTypeSignatureStrategy();
    _curryExpressionTypeSignatureStrategy = new CurryExpressionTypeSignatureStrategy();
    _functionInvocationExpressionTypeSignatureStrategy = new FunctionInvocationExpressionTypeSignatureStrategy();
    _functionReturnExpressionTypeSignatureStrategy = new FunctionReturnExpressionTypeSignatureStrategy();
    _identifierExpressionTypeSignatureStrategy = new IdentifierExpressionTypeSignatureStrategy();
    _lambdaExpressionTypeSignatureStrategy = new LambdaExpressionTypeSignatureStrategy();
    _lambdaReturnExpressionTypeSignatureStrategy = new LambdaReturnExpressionTypeSignatureStrategy();
    _literalExpressionTypeSignatureStrategy = new LiteralExpressionTypeSignatureStrategy();
    _typeTypeSignatureStrategy = new TypeTypeSignatureStrategy();
    _primitiveTypeTypeSignatureStrategy = new PrimitiveTypeTypeSignatureStrategy();
    _customTypeTypeSignatureStrategy = new CustomTypeTypeSignatureStrategy();
    _arrayTypeTypeSignatureStrategy = new ArrayTypeTypeSignatureStrategy();
    _tupleTypeTypeSignatureStrategy = new TupleTypeTypeSignatureStrategy();
    _lambdaTypeTypeSignatureStrategy = new LambdaTypeTypeSignatureStrategy();
    _thisTypeTypeSignatureStrategy = new ThisTypeTypeSignatureStrategy();
}


ArrayAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessExpressionTypeSignatureStrategy() {
    return this->_arrayAccessExpressionTypeSignatureStrategy;
}

ArrayExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayExpressionTypeSignatureStrategy() {
    return this->_arrayExpressionTypeSignatureStrategy;
}

BinaryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getBinaryExpressionTypeSignatureStrategy() {
    return this->_binaryExpressionTypeSignatureStrategy;
}

LogicalExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLogicalExpressionTypeSignatureStrategy() {
    return this->_logicalExpressionTypeSignatureStrategy;
}

ClassMethodInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getClassMethodInvocationExpressionTypeSignatureStrategy() {
    return this->_classMethodInvocationExpressionTypeSignatureStrategy;
}

ClassPropertyAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyAccessExpressionTypeSignatureStrategy() {
    return this->_classPropertyAccessExpressionTypeSignatureStrategy;
}

CurryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getCurryExpressionTypeSignatureStrategy() {
    return this->_curryExpressionTypeSignatureStrategy;
}

FunctionInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionInvocationExpressionTypeSignatureStrategy() {
    return this->_functionInvocationExpressionTypeSignatureStrategy;
}

FunctionReturnExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionReturnExpressionTypeSignatureStrategy() {
    return this->_functionReturnExpressionTypeSignatureStrategy;
}

IdentifierExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getIdentifierExpressionTypeSignatureStrategy() {
    return this->_identifierExpressionTypeSignatureStrategy;
}

LambdaExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaExpressionTypeSignatureStrategy() {
    return this->_lambdaExpressionTypeSignatureStrategy;
}

LambdaReturnExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaReturnExpressionTypeSignatureStrategy() {
    return this->_lambdaReturnExpressionTypeSignatureStrategy;
}

LiteralExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLiteralExpressionTypeSignatureStrategy() {
    return this->_literalExpressionTypeSignatureStrategy;
}

TypeTypeSignatureStrategy* TypeSignatureStrategyMap::getTypeTypeSignatureStrategy() {
    return this->_typeTypeSignatureStrategy;
}

PrimitiveTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getPrimitiveTypeTypeSignatureStrategy() {
    return this->_primitiveTypeTypeSignatureStrategy;
}

CustomTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getCustomTypeTypeSignatureStrategy() {
    return this->_customTypeTypeSignatureStrategy;
}

ArrayTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayTypeTypeSignatureStrategy() {
    return this->_arrayTypeTypeSignatureStrategy;
}

TupleTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleTypeTypeSignatureStrategy() {
    return this->_tupleTypeTypeSignatureStrategy;
}

LambdaTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaTypeTypeSignatureStrategy() {
    return this->_lambdaTypeTypeSignatureStrategy;
}

ThisTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getThisTypeTypeSignatureStrategy() {
    return this->_thisTypeTypeSignatureStrategy;
}