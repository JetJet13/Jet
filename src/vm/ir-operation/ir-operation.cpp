//
// Created by Johny Georges on 2025-09-22.
//

#include "ir-operation.h"

IROperation::IROperation(IROperationType type) {
    _type = type;
}

std::shared_ptr<IROperation> IROperation::markAsUnderlying() {
    _underlyingType = true;
    return shared_from_this();
}

std::shared_ptr<IROperation> IROperation::markAsGlobal() {
    _global = true;
    return shared_from_this();
}

std::shared_ptr<IROperation> IROperation::markCountTowardsRefCount() {
    _countTowardsRefCount = true;
    return shared_from_this();
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
    return _type == IR_COPY_ASSIGNMENT_OP && _global;
}

bool IROperation::isRefAssignment() {
    return _type == IR_REF_ASSIGNMENT_OP;
}

bool IROperation::isRefGlobalAssignment() {
    return _type == IR_REF_ASSIGNMENT_OP && _global;
}

bool IROperation::isFunctionArgument() {
    return _type == IR_FUNCTION_ARGUMENT_OP;
}

bool IROperation::isFunctionReturn() {
    return _type == IR_FUNCTION_RETURN_OP;
}

bool IROperation::isUnderlying() {
    return _underlyingType;
}

bool IROperation::isGlobal() {
    return _global;
}

bool IROperation::incrementRefCount() {
    if (_countTowardsRefCount.has_value()) {
        return _countTowardsRefCount.value();
    }
    return this->isOperandValue() || this->isCopy() || this->isFunctionArgument() || this->isFunctionReturn();
}