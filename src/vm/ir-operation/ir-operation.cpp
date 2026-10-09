// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

bool IROperation::isSharedValueAssignment() {
    return _type == IR_SHARED_VALUE_ASSIGNMENT_OP;
}

bool IROperation::isRefGlobalAssignment() {
    return _type == IR_SHARED_VALUE_ASSIGNMENT_OP && _global;
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