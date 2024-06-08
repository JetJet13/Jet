//
// Created by Johny Georges on 2024-04-30.
//

#include "function-type-signature.h"
#include "../../unknown-type-signature/unknown-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

FunctionTypeSignature::FunctionTypeSignature() {
    _parameterList = new ParameterListTypeSignature();
    _returnType = new UnknownTypeSignature();
}

FunctionTypeSignature::FunctionTypeSignature(ParameterListTypeSignature* parameterList, TypeSignature* returnType) {
    _parameterList = parameterList;
    _returnType = returnType;
}


ParameterListTypeSignature* FunctionTypeSignature::getParameterList() {
    return _parameterList;
}

std::vector<TypeSignature*>* FunctionTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
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

TypeSignature* FunctionTypeSignature::getTargetTypeSignature() {
    return _returnType;
}

bool FunctionTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (FunctionTypeSignature*)otherType;
    return this->getParameterList()->isEqualTo(other->getParameterList()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}

void FunctionTypeSignature::copyFrom(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = (FunctionTypeSignature*)otherType;
    _returnType = other->getReturnType();
    _parameterList = other->getParameterList();
}

void FunctionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}