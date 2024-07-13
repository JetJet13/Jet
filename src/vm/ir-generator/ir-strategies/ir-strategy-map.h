//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_IR_STRATEGY_MAP_H
#define JETLANG_IR_STRATEGY_MAP_H

class IntLiteralIRStrategy;
class FloatLiteralIRStrategy;
class CharLiteralIRStrategy;
class StringLiteralIRStrategy;
class BoolLiteralIRStrategy;
class LiteralExpressionIRStrategy;
class BinaryExpressionIRStrategy;
class LogicalExpressionIRStrategy;
class ArrayExpressionIRStrategy;
class ArrayAccessExpressionIRStrategy;
class StructExpressionIRStrategy;
class UnaryExpressionIRStrategy;
class TupleExpressionIRStrategy;
class IdentifierExpressionIRStrategy;
class VariableDeclarationIRStrategy;
class FunctionDeclarationIRStrategy;
class FunctionParameterListIRStrategy;
class FunctionReturnExpressionIRStrategy;
// Type Signature IR Strategies
class ArrayTypeSignatureIRStrategy;
class LiteralTypeSignatureIRStrategy;
class ClassTypeSignatureIRStrategy;
class EnumTypeSignatureIRStrategy;
class FunctionTypeSignatureIRStrategy;
class LambdaTypeSignatureIRStrategy;
class ProcedureTypeSignatureIRStrategy;
class LiteralTypeSignatureIRStrategy;
class ParameterListTypeSignatureIRStrategy;
class ParameterTypeSignatureIRStrategy;
class StructTypeSignatureIRStrategy;
class TupleTypeSignatureIRStrategy;
class VoidTypeSignatureIRStrategy;

class IRStrategyMap {
private:
    IntLiteralIRStrategy* _intLiteralIRStrategy;
    FloatLiteralIRStrategy* _floatLiteralIRStrategy;
    CharLiteralIRStrategy* _charLiteralIRStrategy;
    StringLiteralIRStrategy* _stringLiteralIRStrategy;
    BoolLiteralIRStrategy* _boolLiteralIRStrategy;
    LiteralExpressionIRStrategy* _literalExpressionIRStrategy;
    BinaryExpressionIRStrategy* _binaryExpressionIRStrategy;
    LogicalExpressionIRStrategy* _logicalExpressionIRStrategy;
    ArrayExpressionIRStrategy* _arrayExpressionIRStrategy;
    ArrayAccessExpressionIRStrategy* _arrayAccessExpressionIRStrategy;
    StructExpressionIRStrategy* _structExpressionIRStrategy;
    UnaryExpressionIRStrategy* _unaryExpressionIRStrategy;
    TupleExpressionIRStrategy* _tupleExpressionIRStrategy;
    IdentifierExpressionIRStrategy* _identifierExpressionIRStrategy;
    VariableDeclarationIRStrategy* _variableDeclarationIRStrategy;
    FunctionDeclarationIRStrategy* _functionDeclarationIRStrategy;
    FunctionParameterListIRStrategy* _functionParameterListIRStrategy;
    FunctionReturnExpressionIRStrategy* _functionReturnExpressionIRStrategy;
    // Type Signature IR Strategies
    ArrayTypeSignatureIRStrategy* _arrayTypeSignatureIRStrategy;
    LiteralTypeSignatureIRStrategy* _literalTypeSignatureIRStrategy;
    ClassTypeSignatureIRStrategy* _classTypeSignatureIRStrategy;
    EnumTypeSignatureIRStrategy* _enumTypeSignatureIRStrategy;
    FunctionTypeSignatureIRStrategy* _functionTypeSignatureIRStrategy;
    LambdaTypeSignatureIRStrategy* _lambdaTypeSignatureIRStrategy;
    ProcedureTypeSignatureIRStrategy* _procedureTypeSignatureIRStrategy;
    ParameterListTypeSignatureIRStrategy* _parameterListTypeSignatureIRStrategy;
    ParameterTypeSignatureIRStrategy* _parameterTypeSignatureIRStrategy;
    StructTypeSignatureIRStrategy* _structTypeSignatureIRStrategy;
    TupleTypeSignatureIRStrategy* _tupleTypeSignatureIRStrategy;
public:
    IRStrategyMap();
    IntLiteralIRStrategy* getIntLiteralIRStrategy();
    FloatLiteralIRStrategy* getFloatLiteralIRStrategy();
    CharLiteralIRStrategy* getCharLiteralIRStrategy();
    StringLiteralIRStrategy* getStringLiteralIRStrategy();
    BoolLiteralIRStrategy* getBoolLiteralIRStrategy();
    LiteralExpressionIRStrategy* getLiteralExpressionIRStrategy();
    BinaryExpressionIRStrategy* getBinaryExpressionIRStrategy();
    LogicalExpressionIRStrategy* getLogicalExpressionIRStrategy();
    ArrayExpressionIRStrategy* getArrayExpressionIRStrategy();
    ArrayAccessExpressionIRStrategy* getArrayAccessExpressionIRStrategy();
    StructExpressionIRStrategy* getStructExpressionIRStrategy();
    UnaryExpressionIRStrategy* getUnaryExpressionIRStrategy();
    TupleExpressionIRStrategy* getTupleExpressionIRStrategy();
    IdentifierExpressionIRStrategy* getIdentifierExpressionIRStrategy();
    VariableDeclarationIRStrategy* getVariableDeclarationIRStrategy();
    FunctionDeclarationIRStrategy* getFunctionDeclarationIRStrategy();
    FunctionParameterListIRStrategy* getFunctionParameterListIRStrategy();
    FunctionReturnExpressionIRStrategy* getFunctionReturnExpressionIRStrategy();
    // Type Signature IR Strategies
    ArrayTypeSignatureIRStrategy* getArrayTypeSignatureIRStrategy();
    LiteralTypeSignatureIRStrategy* getLiteralTypeSignatureIRStrategy();
    ClassTypeSignatureIRStrategy* getClassTypeSignatureIRStrategy();
    EnumTypeSignatureIRStrategy* getEnumTypeSignatureIRStrategy();
    FunctionTypeSignatureIRStrategy* getFunctionTypeSignatureIRStrategy();
    LambdaTypeSignatureIRStrategy* getLambdaTypeSignatureIRStrategy();
    ProcedureTypeSignatureIRStrategy* getProcedureTypeSignatureIRStrategy();
    ParameterListTypeSignatureIRStrategy* getParameterListTypeSignatureIRStrategy();
    ParameterTypeSignatureIRStrategy* getParameterTypeSignatureIRStrategy();
    StructTypeSignatureIRStrategy* getStructTypeSignatureIRStrategy();
    TupleTypeSignatureIRStrategy* getTupleTypeSignatureIRStrategy();

};

#endif //JETLANG_IR_STRATEGY_MAP_H
