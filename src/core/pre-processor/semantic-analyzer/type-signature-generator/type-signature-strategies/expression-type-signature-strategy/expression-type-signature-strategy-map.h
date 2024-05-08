//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_EXPRESSION_TYPE_SIGNATURE_STRATEGY_MAP_H
#define JETLANG_EXPRESSION_TYPE_SIGNATURE_STRATEGY_MAP_H

#include "strategies/binary-expression-type-signature-strategy/binary-expression-type-signature-strategy.h"
#include "strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
#include "strategies/array-expression-type-signature-strategy/array-expression-type-signature-strategy.h"
#include "strategies/class-method-invocation-expression-type-signature-strategy/class-method-invocation-expression-type-signature-strategy.h"
#include "strategies/class-property-expression-type-signature-strategy/class-property-access-expression-type-signature-strategy.h"
#include "strategies/curry-expression-type-signature-strategy/curry-expression-type-signature-strategy.h"
#include "strategies/function-invocation-expression-type-signature-strategy/function-invocation-expression-type-signature-strategy.h"
#include "strategies/function-return-expression-type-signature-strategy/function-return-expression-type-signature-strategy.h"
#include "strategies/identifier-expression-type-signature-strategy/identifier-expression-type-signature-strategy.h"

class ExpressionTypeSignatureStrategyMap {
private:
    ArrayAccessExpressionTypeSignatureStrategy* _arrayAccessExpressionTypeSignatureStrategy;
    ArrayExpressionTypeSignatureStrategy* _arrayExpressionTypeSignatureStrategy;
    BinaryExpressionTypeSignatureStrategy* _binaryExpressionTypeSignatureStrategy;
    ClassMethodInvocationExpressionTypeSignatureStrategy* _classMethodInvocationExpressionTypeSignatureStrategy;
    ClassPropertyAccessExpressionTypeSignatureStrategy* _classPropertyAccessExpressionTypeSignatureStrategy;
    CurryExpressionTypeSignatureStrategy* _curryExpressionTypeSignatureStrategy;
    FunctionInvocationExpressionTypeSignatureStrategy* _functionInvocationExpressionTypeSignatureStrategy;
    FunctionReturnExpressionTypeSignatureStrategy* _functionReturnExpressionTypeSignatureStrategy;
    IdentifierExpressionTypeSignatureStrategy* _identifierExpressionTypeSignatureStrategy;
//    LambdaExpressionTypeSignatureStrategy* _lambdaExpressionTypeSignatureStrategy;
//    LambdaReturnExpressionTypeSignatureStrategy* _lambdaReturnExpressionTypeSignatureStrategy;
//    LiteralExpressionTypeSignatureStrategy* _literalExpressionTypeSignatureStrategy;
    LogicalExpressionTypeSignatureStrategy* _logicalExpressionTypeSignatureStrategy;
//    NewClassInstanceExpressionTypeSignatureStrategy* _newClassInstanceExpressionTypeSignatureStrategy;
//    ObjectAccessExpressionTypeSignatureStrategy* _objectAccessExpressionTypeSignatureStrategy;
//    StructExpressionTypeSignatureStrategy* _structExpressionTypeSignatureStrategy;
//    ThisExpressionTypeSignatureStrategy* _thisExpressionTypeSignatureStrategy;
//    TupleAccessExpressionTypeSignatureStrategy* _tupleAccessExpressionTypeSignatureStrategy;
//    TupleExpressionTypeSignatureStrategy* _tupleExpressionTypeSignatureStrategy;
//    UnaryExpressionTypeSignatureStrategy* _unaryExpressionTypeSignatureStrategy;
public:
    ExpressionTypeSignatureStrategyMap();
    ArrayAccessExpressionTypeSignatureStrategy* getArrayAccessExpressionTypeSignatureStrategy();
    ArrayExpressionTypeSignatureStrategy* getArrayExpressionTypeSignatureStrategy();
    BinaryExpressionTypeSignatureStrategy* getBinaryExpressionTypeSignatureStrategy();
    ClassMethodInvocationExpressionTypeSignatureStrategy* getClassMethodInvocationExpressionTypeSignatureStrategy();
    ClassPropertyAccessExpressionTypeSignatureStrategy* getClassPropertyAccessExpressionTypeSignatureStrategy();
    CurryExpressionTypeSignatureStrategy* getCurryExpressionTypeSignatureStrategy();
    FunctionInvocationExpressionTypeSignatureStrategy* getFunctionInvocationExpressionTypeSignatureStrategy();
    FunctionReturnExpressionTypeSignatureStrategy* getFunctionReturnExpressionTypeSignatureStrategy();
    IdentifierExpressionTypeSignatureStrategy* getIdentifierExpressionTypeSignatureStrategy();
//    LambdaExpressionTypeSignatureStrategy* getLambdaExpressionTypeSignatureStrategy();
//    LambdaReturnExpressionTypeSignatureStrategy* getLambdaReturnExpressionTypeSignatureStrategy();
//    LiteralExpressionTypeSignatureStrategy* getLiteralExpressionTypeSignatureStrategy();
    LogicalExpressionTypeSignatureStrategy* getLogicalExpressionTypeSignatureStrategy();
//    NewClassInstanceExpressionTypeSignatureStrategy* getNewClassInstanceExpressionTypeSignatureStrategy();
//    ObjectAccessExpressionTypeSignatureStrategy* getObjectAccessExpressionTypeSignatureStrategy();
//    StructExpressionTypeSignatureStrategy* getStructExpressionTypeSignatureStrategy();
//    ThisExpressionTypeSignatureStrategy* getThisExpressionTypeSignatureStrategy();
//    TupleAccessExpressionTypeSignatureStrategy* getTupleAccessExpressionTypeSignatureStrategy();
//    TupleExpressionTypeSignatureStrategy* getTupleExpressionTypeSignatureStrategy();
//    UnaryExpressionTypeSignatureStrategy* getUnaryExpressionTypeSignatureStrategy();
};

#endif //JETLANG_EXPRESSION_TYPE_SIGNATURE_STRATEGY_MAP_H
