//
// Created by Johny Georges on 2024-05-16.
//

#include "function-invocation-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

FunctionInvocationTypeSignature::FunctionInvocationTypeSignature() {
    _invocableTypeSignature = new FunctionTypeSignature();
}

FunctionInvocationTypeSignature::FunctionInvocationTypeSignature(InvocableTypeSignature* invocableTypeSignature) {
    _invocableTypeSignature = invocableTypeSignature;
}

InvocableTypeSignature* FunctionInvocationTypeSignature::getFunctionType() {
    return _invocableTypeSignature;
}

TypeSignature* FunctionInvocationTypeSignature::getReturnType() {
    return _invocableTypeSignature->getReturnType();
}

std::string FunctionInvocationTypeSignature::toString() {
    return "FUNCTION_INVOCATION_TYPE_SIGNATURE";
}

TypeSource FunctionInvocationTypeSignature::getTypeSource() {
    return FUNCTION_INVOCATION_TYPE_SOURCE;
}

TypeSource FunctionInvocationTypeSignature::getTypeTarget() {
    return _invocableTypeSignature->getReturnType()->getTypeTarget();
}

TypeSignature* FunctionInvocationTypeSignature::getTargetTypeSignature() {
    return _invocableTypeSignature->getReturnType();
}

bool FunctionInvocationTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (FunctionInvocationTypeSignature*)otherType;
    return this->getFunctionType()->isEqualTo(other->getFunctionType());
}

void FunctionInvocationTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _invocableTypeSignature->getReturnType()->print();
    Logger::log("----------");
}