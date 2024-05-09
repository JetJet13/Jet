//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-map.h"

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
    _typeTypeSignatureStrategy = new TypeTypeSignatureStrategy();
    _primitiveTypeTypeSignatureStrategy = new PrimitiveTypeTypeSignatureStrategy();
    _customTypeTypeSignatureStrategy = new CustomTypeTypeSignatureStrategy();
    _arrayTypeTypeSignatureStrategy = new ArrayTypeTypeSignatureStrategy();
    _intLiteralTypeTypeSignatureStrategy = new IntLiteralTypeTypeSignatureStrategy();
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

IntLiteralTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getIntLiteralTypeTypeSignatureStrategy() {
    return this->_intLiteralTypeTypeSignatureStrategy;
}