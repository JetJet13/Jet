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
    int STRING;
    int POINTER;
    int STRUCT;
    int ARRAY;
};

const IRTypeIdMap IR_TYPE_ID = {
        .INT = 1,
        .FLOAT = 2,
        .CHAR = 3,
        .BOOL = 4,
        .STRING = 5,
        .POINTER = 1000,
        .STRUCT = 2000,
        .ARRAY = 3000
};
#endif //JETLANG_IR_TYPE_ID_H
