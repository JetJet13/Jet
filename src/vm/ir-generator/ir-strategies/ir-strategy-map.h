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
class BinaryExpressionIRStrategy;
class LogicalExpressionIRStrategy;
class ArrayExpressionIRStrategy;
class ArrayAccessExpressionIRStrategy;
class StructExpressionIRStrategy;
class UnaryExpressionIRStrategy;
class TupleExpressionIRStrategy;
class IdentifierIRStrategy;
class VariableDeclarationIRStrategy;
// Type Signature IR Strategies
class ArrayTypeSignatureIRStrategy;

class IRStrategyMap {
private:
    IntLiteralIRStrategy* _intLiteralIRStrategy;
    FloatLiteralIRStrategy* _floatLiteralIRStrategy;
    CharLiteralIRStrategy* _charLiteralIRStrategy;
    StringLiteralIRStrategy* _stringLiteralIRStrategy;
    BoolLiteralIRStrategy* _boolLiteralIRStrategy;
    BinaryExpressionIRStrategy* _binaryExpressionIRStrategy;
    LogicalExpressionIRStrategy* _logicalExpressionIRStrategy;
    ArrayExpressionIRStrategy* _arrayExpressionIRStrategy;
    ArrayAccessExpressionIRStrategy* _arrayAccessExpressionIRStrategy;
    StructExpressionIRStrategy* _structExpressionIRStrategy;
    UnaryExpressionIRStrategy* _unaryExpressionIRStrategy;
    TupleExpressionIRStrategy* _tupleExpressionIRStrategy;
    IdentifierIRStrategy* _identifierIRStrategy;
    VariableDeclarationIRStrategy* _variableDeclarationIRStrategy;
    // Type Signature IR Strategies
    ArrayTypeSignatureIRStrategy* _arrayTypeSignatureIRStrategy;
public:
    IRStrategyMap();
    IntLiteralIRStrategy* getIntLiteralIRStrategy();
    FloatLiteralIRStrategy* getFloatLiteralIRStrategy();
    CharLiteralIRStrategy* getCharLiteralIRStrategy();
    StringLiteralIRStrategy* getStringLiteralIRStrategy();
    BoolLiteralIRStrategy* getBoolLiteralIRStrategy();
    BinaryExpressionIRStrategy* getBinaryExpressionIRStrategy();
    LogicalExpressionIRStrategy* getLogicalExpressionIRStrategy();
    ArrayExpressionIRStrategy* getArrayExpressionIRStrategy();
    ArrayAccessExpressionIRStrategy* getArrayAccessExpressionIRStrategy();
    StructExpressionIRStrategy* getStructExpressionIRStrategy();
    UnaryExpressionIRStrategy* getUnaryExpressionIRStrategy();
    TupleExpressionIRStrategy* getTupleExpressionIRStrategy();
    IdentifierIRStrategy* getIdentifierIRStrategy();
    VariableDeclarationIRStrategy* getVariableDeclarationIRStrategy();
    // Type Signature IR Strategies
    ArrayTypeSignatureIRStrategy* getArrayTypeSignatureIRStrategy();
};

#endif //JETLANG_IR_STRATEGY_MAP_H
