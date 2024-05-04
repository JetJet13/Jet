//
// Created by Johny Georges on 2024-04-30.
//

#include "function-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

FunctionTypeSignature::FunctionTypeSignature(std::string name, ParameterListTypeSignature* parameterList, TypeSignature* returnType) {
    _name = name;
    _parameterList = parameterList;
    _returnType = returnType;
}

std::string FunctionTypeSignature::getName() {
    return _name;
}

ParameterListTypeSignature* FunctionTypeSignature::getParameterList() {
    return _parameterList;
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
    return this->getName() == other->getName() &&
           this->getParameterList()->isEqualTo(other->getParameterList()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}

void FunctionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}