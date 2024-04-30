//
// Created by Johny Georges on 2024-04-30.
//

#include "function-type.h"

FunctionType::FunctionType(std::vector<BaseType*>* parameterTypes, BaseType* returnType) {
    _parameterTypes = parameterTypes;
    _returnType = returnType;
}

std::vector<BaseType*>* FunctionType::getParameterTypes() {
    return _parameterTypes;
}

BaseType* FunctionType::getReturnType() {
    return _returnType;
}

TypeSource FunctionType::getTypeSource() {
    return FUNCTION_TYPE_SOURCE;
}

bool FunctionType::isEqualTo(BaseType* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (FunctionType*)otherType;
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }

    return _returnType->isEqualTo(other->getReturnType());
}