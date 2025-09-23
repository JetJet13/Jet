//
// Created by Johny Georges on 2025-09-22.
//

#include "ir-operation.h"

IROperation::IROperation(IROperationType type) {
    _type = type;
}

bool IROperation::isOperand() {
    return _type == IR_OPERAND_POINTER_OP || _type == IR_OPERAND_VALUE_OP;
}

bool IROperation::isOperandValue() {
    return _type == IR_OPERAND_VALUE_OP;
}

bool IROperation::isOperandPointer() {
    return _type == IR_OPERAND_POINTER_OP;
}

bool IROperation::isCopy() {
    return _type == IR_COPY_ASSIGNMENT_OP;
}

bool IROperation::isCopyGlobal() {
    return _type == IR_COPY_GLOBAL_ASSIGNMENT_OP;
}

bool IROperation::isCopyReassignment() {
    return _type == IR_COPY_REASSIGNMENT_OP;
}

bool IROperation::isRefAssignment() {
    return _type == IR_REF_ASSIGNMENT_OP;
}

bool IROperation::isRefGlobalAssignment() {
    return _type == IR_REF_GLOBAL_ASSIGNMENT_OP;
}

bool IROperation::isFunctionArgument() {
    return _type == IR_FUNCTION_ARGUMENT_OP;
}

bool IROperation::isFunctionReturn() {
    return _type == IR_FUNCTION_RETURN_OP;
}
