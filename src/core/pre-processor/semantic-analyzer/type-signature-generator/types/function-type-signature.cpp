//
// Created by Johny Georges on 2024-04-30.
//

#include "function-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

FunctionTypeSignature::FunctionTypeSignature(std::vector<TypeSignature*>* parameterTypes, TypeSignature* returnType) {
    _parameterTypes = parameterTypes;
    _returnType = returnType;
}

std::vector<TypeSignature*>* FunctionTypeSignature::getParameterTypes() {
    return _parameterTypes;
}

TypeSignature* FunctionTypeSignature::getReturnType() {
    return _returnType;
}

std::string FunctionTypeSignature::toString() {
    return "FUNCTION_TYPE_SIGNATURE";
}

TypeSource FunctionTypeSignature::getTypeSource() {
    return FUNCTION_TYPE_SOURCE;
}

bool FunctionTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (FunctionTypeSignature*)otherType;
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }

    return _returnType->isEqualTo(other->getReturnType());
}

void FunctionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        _parameterTypes->at(i)->print();
    }
    Logger::log("----------");
}