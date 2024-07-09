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
// Type Signature IR Strategies
class ArrayTypeSignatureIRStrategy;

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
    // Type Signature IR Strategies
    ArrayTypeSignatureIRStrategy* _arrayTypeSignatureIRStrategy;
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
    // Type Signature IR Strategies
    ArrayTypeSignatureIRStrategy* getArrayTypeSignatureIRStrategy();
};

#endif //JETLANG_IR_STRATEGY_MAP_H
