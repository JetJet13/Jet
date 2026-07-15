//
// Created by Johny Georges on 2025-09-22.
//

#ifndef JETLANG_IR_OPERATION_H
#define JETLANG_IR_OPERATION_H

#include <optional>
#include "../types/ir-operation-type.h"

class IROperation : public std::enable_shared_from_this<IROperation> {
private:
    IROperationType _type;
    bool _global = false;
    bool _underlyingType = false;
    std::optional<bool> _countTowardsRefCount = {};
public:
    IROperation(IROperationType type);
    std::shared_ptr<IROperation> markAsUnderlying();
    std::shared_ptr<IROperation> markAsGlobal();
    std::shared_ptr<IROperation> markCountTowardsRefCount();
    bool isOperand();
    bool isOperandValue();
    bool isOperandPointer();
    bool isCopy();
    bool isCopyGlobal();
    bool isSharedValueAssignment();
    bool isRefGlobalAssignment();
    bool isFunctionArgument();
    bool isFunctionReturn();
    bool isUnderlying();
    bool isGlobal();
    bool incrementRefCount();
};

#endif //JETLANG_IR_OPERATION_H
