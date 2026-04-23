//
// Created by Johny Georges on 2025-04-11.
//

#ifndef JETLANG_IR_TYPE_ID_H
#define JETLANG_IR_TYPE_ID_H
struct IRTypeIdMap {
    int INT;
    int FLOAT;
    int CHAR;
    int BOOL;
    int LITERAL;
    int STRING;
    int POINTER;
    int REF;
    int CAPTURED_VARIABLE;
    int STRUCT;
    int STRUCT_REF;
    int ARRAY;
    int INVOCABLE;
    int VOID;
};

const IRTypeIdMap IR_TYPE_ID = {
        .INT = 1,
        .FLOAT = 2,
        .CHAR = 3,
        .BOOL = 4,
        .LITERAL = 500,
        .STRING = 501,
        .POINTER = 1000,
        .REF = 1001,
        .CAPTURED_VARIABLE = 1002,
        .STRUCT = 2000,
        .STRUCT_REF = 2001,
        .ARRAY = 3000,
        .INVOCABLE = 4000,
        .VOID = 9999
};
#endif //JETLANG_IR_TYPE_ID_H
