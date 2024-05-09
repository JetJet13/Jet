//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_MAP_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_MAP_H

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
#include "expression-type-signature-strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/int-literal-type-type-signature-strategy/int-literal-type-type-signature-strategy.h"

class TypeSignatureStrategyMap {
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
    LambdaExpressionTypeSignatureStrategy* _lambdaExpressionTypeSignatureStrategy;
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
      TypeTypeSignatureStrategy* _typeTypeSignatureStrategy;
      PrimitiveTypeTypeSignatureStrategy* _primitiveTypeTypeSignatureStrategy;
      CustomTypeTypeSignatureStrategy* _customTypeTypeSignatureStrategy;
      ArrayTypeTypeSignatureStrategy* _arrayTypeTypeSignatureStrategy;
      IntLiteralTypeTypeSignatureStrategy* _intLiteralTypeTypeSignatureStrategy;
public:
    TypeSignatureStrategyMap();
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
      TypeTypeSignatureStrategy* getTypeTypeSignatureStrategy();
      PrimitiveTypeTypeSignatureStrategy* getPrimitiveTypeTypeSignatureStrategy();
      CustomTypeTypeSignatureStrategy* getCustomTypeTypeSignatureStrategy();
      ArrayTypeTypeSignatureStrategy* getArrayTypeTypeSignatureStrategy();
      IntLiteralTypeTypeSignatureStrategy* getIntLiteralTypeTypeSignatureStrategy();
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_MAP_H
