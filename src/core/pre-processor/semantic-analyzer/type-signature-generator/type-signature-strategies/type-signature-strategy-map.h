//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_MAP_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_MAP_H

// forward declaration to prevent
// circular dependency error
class ArrayAccessExpressionTypeSignatureStrategy;
class ArrayExpressionTypeSignatureStrategy;
class BinaryExpressionTypeSignatureStrategy;
class ClassMethodInvocationExpressionTypeSignatureStrategy;
class ClassPropertyAccessExpressionTypeSignatureStrategy;
class CurryExpressionTypeSignatureStrategy;
class FunctionInvocationExpressionTypeSignatureStrategy;
class FunctionReturnExpressionTypeSignatureStrategy;
class IdentifierExpressionTypeSignatureStrategy;
class LambdaExpressionTypeSignatureStrategy;
class LambdaReturnExpressionTypeSignatureStrategy;
class LiteralExpressionTypeSignatureStrategy;
class LogicalExpressionTypeSignatureStrategy;
class NewClassInstanceExpressionTypeSignatureStrategy;
class ObjectAccessExpressionTypeSignatureStrategy;
class StructExpressionTypeSignatureStrategy;
class ThisExpressionTypeSignatureStrategy;
class TupleAccessExpressionTypeSignatureStrategy;
class TupleExpressionTypeSignatureStrategy;
class UnaryExpressionTypeSignatureStrategy;
class TypeTypeSignatureStrategy;
class PrimitiveTypeTypeSignatureStrategy;
class CustomTypeTypeSignatureStrategy;
class ArrayTypeTypeSignatureStrategy;
class TupleTypeTypeSignatureStrategy;
class LambdaTypeTypeSignatureStrategy;
class ThisTypeTypeSignatureStrategy;
class EnumKeyValueTypeSignatureStrategy;
class EnumTypeSignatureStrategy;



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
    LambdaReturnExpressionTypeSignatureStrategy* _lambdaReturnExpressionTypeSignatureStrategy;
    LiteralExpressionTypeSignatureStrategy* _literalExpressionTypeSignatureStrategy;
    LogicalExpressionTypeSignatureStrategy* _logicalExpressionTypeSignatureStrategy;
    NewClassInstanceExpressionTypeSignatureStrategy* _newClassInstanceExpressionTypeSignatureStrategy;
    ObjectAccessExpressionTypeSignatureStrategy* _objectAccessExpressionTypeSignatureStrategy;
    StructExpressionTypeSignatureStrategy* _structExpressionTypeSignatureStrategy;
    ThisExpressionTypeSignatureStrategy* _thisExpressionTypeSignatureStrategy;
    TupleAccessExpressionTypeSignatureStrategy* _tupleAccessExpressionTypeSignatureStrategy;
    TupleExpressionTypeSignatureStrategy* _tupleExpressionTypeSignatureStrategy;
    UnaryExpressionTypeSignatureStrategy* _unaryExpressionTypeSignatureStrategy;
    TypeTypeSignatureStrategy* _typeTypeSignatureStrategy;
    PrimitiveTypeTypeSignatureStrategy* _primitiveTypeTypeSignatureStrategy;
    CustomTypeTypeSignatureStrategy* _customTypeTypeSignatureStrategy;
    ArrayTypeTypeSignatureStrategy* _arrayTypeTypeSignatureStrategy;
    TupleTypeTypeSignatureStrategy* _tupleTypeTypeSignatureStrategy;
    LambdaTypeTypeSignatureStrategy* _lambdaTypeTypeSignatureStrategy;
    ThisTypeTypeSignatureStrategy* _thisTypeTypeSignatureStrategy;
    EnumKeyValueTypeSignatureStrategy* _enumKeyValueTypeSignatureStrategy;
    EnumTypeSignatureStrategy* _enumTypeSignatureStrategy;
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
    LambdaExpressionTypeSignatureStrategy* getLambdaExpressionTypeSignatureStrategy();
    LambdaReturnExpressionTypeSignatureStrategy* getLambdaReturnExpressionTypeSignatureStrategy();
    LiteralExpressionTypeSignatureStrategy* getLiteralExpressionTypeSignatureStrategy();
    LogicalExpressionTypeSignatureStrategy* getLogicalExpressionTypeSignatureStrategy();
    NewClassInstanceExpressionTypeSignatureStrategy* getNewClassInstanceExpressionTypeSignatureStrategy();
    ObjectAccessExpressionTypeSignatureStrategy* getObjectAccessExpressionTypeSignatureStrategy();
    StructExpressionTypeSignatureStrategy* getStructExpressionTypeSignatureStrategy();
    ThisExpressionTypeSignatureStrategy* getThisExpressionTypeSignatureStrategy();
    TupleAccessExpressionTypeSignatureStrategy* getTupleAccessExpressionTypeSignatureStrategy();
    TupleExpressionTypeSignatureStrategy* getTupleExpressionTypeSignatureStrategy();
    UnaryExpressionTypeSignatureStrategy* getUnaryExpressionTypeSignatureStrategy();
    TypeTypeSignatureStrategy* getTypeTypeSignatureStrategy();
    PrimitiveTypeTypeSignatureStrategy* getPrimitiveTypeTypeSignatureStrategy();
    CustomTypeTypeSignatureStrategy* getCustomTypeTypeSignatureStrategy();
    ArrayTypeTypeSignatureStrategy* getArrayTypeTypeSignatureStrategy();
    TupleTypeTypeSignatureStrategy* getTupleTypeTypeSignatureStrategy();
    LambdaTypeTypeSignatureStrategy* getLambdaTypeTypeSignatureStrategy();
    ThisTypeTypeSignatureStrategy* getThisTypeTypeSignatureStrategy();
    EnumKeyValueTypeSignatureStrategy* getEnumKeyValueTypeSignatureStrategy();
    EnumTypeSignatureStrategy* getEnumTypeSignatureStrategy();
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_MAP_H
