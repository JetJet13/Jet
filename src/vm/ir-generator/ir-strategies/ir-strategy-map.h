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

class IRStrategyMap {
private:
    IntLiteralIRStrategy* _intLiteralIRStrategy;
    FloatLiteralIRStrategy* _floatLiteralIRStrategy;
    CharLiteralIRStrategy* _charLiteralIRStrategy;
    StringLiteralIRStrategy* _stringLiteralIRStrategy;
    BoolLiteralIRStrategy* _boolLiteralIRStrategy;
public:
    IRStrategyMap();
    IntLiteralIRStrategy* getIntLiteralIRStrategy();
    FloatLiteralIRStrategy* getFloatLiteralIRStrategy();
    CharLiteralIRStrategy* getCharLiteralIRStrategy();
    StringLiteralIRStrategy* getStringLiteralIRStrategy();
    BoolLiteralIRStrategy* getBoolLiteralIRStrategy();
};

#endif //JETLANG_IR_STRATEGY_MAP_H
