//
// Created by Johny Georges on 2026-08-22.
//

#include "variable-context.h"

VariableContext::VariableContext() {}

void VariableContext::markAsConstant() {
    _isConstant = true;
}

bool VariableContext::isConstant() {
    return _isConstant;
}