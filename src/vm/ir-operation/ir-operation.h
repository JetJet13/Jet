//
// Created by Johny Georges on 2025-09-22.
//

#ifndef JETLANG_IR_OPERATION_H
#define JETLANG_IR_OPERATION_H

#include "../types/ir-operation-type.h"

class IROperation {
private:
    IROperationType _type;
    bool _global;
    bool _underlyingType;
public:
    IROperation(IROperationType type);
    IROperation* markAsUnderlying();
    IROperation* markAsGlobal();
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
    bool isUnderlying();
    bool isGlobal();
};

#endif //JETLANG_IR_OPERATION_H
