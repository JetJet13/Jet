//
// Created by Johny Georges on 2025-11-22.
//

#ifndef JETLANG_IR_BLOCK_TYPE_H
#define JETLANG_IR_BLOCK_TYPE_H
typedef enum {
    IR_BASIC_BT,
    IR_IF_BT,
    IR_IF_THEN_BT,
    IR_IF_ELSE_BT,
    IR_WHILE_BT,
    IR_FOR_LOOP_BT,
    IR_FOR_IN_BT
} IRBlockType;
#endif //JETLANG_IR_BLOCK_TYPE_H
