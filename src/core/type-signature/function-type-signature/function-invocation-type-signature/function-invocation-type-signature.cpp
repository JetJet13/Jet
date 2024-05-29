//
// Created by Johny Georges on 2024-05-16.
//

#include "function-invocation-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

FunctionInvocationTypeSignature::FunctionInvocationTypeSignature() {
    _functionTypeSignature = new FunctionTypeSignature();
}

FunctionInvocationTypeSignature::FunctionInvocationTypeSignature(FunctionTypeSignature* functionTypeSignature) {
    _functionTypeSignature = functionTypeSignature;
}

FunctionTypeSignature* FunctionInvocationTypeSignature::getFunctionType() {
    return _functionTypeSignature;
}

TypeSignature* FunctionInvocationTypeSignature::getReturnType() {
    return _functionTypeSignature->getReturnType();
}

std::string FunctionInvocationTypeSignature::toString() {
    return "FUNCTION_INVOCATION_TYPE_SIGNATURE";
}

TypeSource FunctionInvocationTypeSignature::getTypeSource() {
    return FUNCTION_INVOCATION_TYPE_SOURCE;
}

TypeSource FunctionInvocationTypeSignature::getTypeTarget() {
    return _functionTypeSignature->getReturnType()->getTypeTarget();
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
    _functionTypeSignature->getReturnType()->print();
    Logger::log("----------");
}