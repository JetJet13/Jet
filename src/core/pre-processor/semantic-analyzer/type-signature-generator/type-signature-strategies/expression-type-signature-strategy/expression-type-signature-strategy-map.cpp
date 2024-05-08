//
// Created by Johny Georges on 2024-05-06.
//

#include "expression-type-signature-strategy-map.h"

ExpressionTypeSignatureStrategyMap::ExpressionTypeSignatureStrategyMap() {
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
}

ArrayAccessExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getArrayAccessExpressionTypeSignatureStrategy() {
    return this->_arrayAccessExpressionTypeSignatureStrategy;
}

ArrayExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getArrayExpressionTypeSignatureStrategy() {
    return this->_arrayExpressionTypeSignatureStrategy;
}

BinaryExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getBinaryExpressionTypeSignatureStrategy() {
    return this->_binaryExpressionTypeSignatureStrategy;
}

LogicalExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getLogicalExpressionTypeSignatureStrategy() {
    return this->_logicalExpressionTypeSignatureStrategy;
}

ClassMethodInvocationExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getClassMethodInvocationExpressionTypeSignatureStrategy() {
    return this->_classMethodInvocationExpressionTypeSignatureStrategy;
}

ClassPropertyAccessExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getClassPropertyAccessExpressionTypeSignatureStrategy() {
    return this->_classPropertyAccessExpressionTypeSignatureStrategy;
}

CurryExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getCurryExpressionTypeSignatureStrategy() {
    return this->_curryExpressionTypeSignatureStrategy;
}

FunctionInvocationExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getFunctionInvocationExpressionTypeSignatureStrategy() {
    return this->_functionInvocationExpressionTypeSignatureStrategy;
}

FunctionReturnExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getFunctionReturnExpressionTypeSignatureStrategy() {
    return this->_functionReturnExpressionTypeSignatureStrategy;
}

IdentifierExpressionTypeSignatureStrategy* ExpressionTypeSignatureStrategyMap::getIdentifierExpressionTypeSignatureStrategy() {
    return this->_identifierExpressionTypeSignatureStrategy;
}