//
// Created by Johny Georges on 2025-09-22.
//

#ifndef JETLANG_IR_OPERATION_H
#define JETLANG_IR_OPERATION_H

#include "../types/ir-operation-type.h"

class IROperation {
private:
    IROperationType _type;
public:
    IROperation(IROperationType type);
    bool isOperand();
    bool isOperandValue();
    bool isOperandPointer();
    bool isCopy();
    bool isCopyGlobal();
    bool isCopyReassignment();
    bool isCopyReassignmentGlobal();
    bool isRefAssignment();
    bool isRefGlobalAssignment();
    bool isFunctionArgument();
    bool isFunctionReturn();

};

#endif //JETLANG_IR_OPERATION_H
