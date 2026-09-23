//
// Created by Johny Georges on 2024-04-30.
//

#include "function-type-signature.h"
#include "../../unknown-type-signature/unknown-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

FunctionTypeSignature::FunctionTypeSignature() {
    _parameterList = std::make_shared<ParameterListTypeSignature>();
    _returnType = std::make_shared<UnknownTypeSignature>();
}

FunctionTypeSignature::FunctionTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList, std::shared_ptr<TypeSignature> returnType) {
    _parameterList = parameterList;
    _returnType = returnType;
}

std::shared_ptr<ParameterListTypeSignature> FunctionTypeSignature::getParameterList() {
    return _parameterList;
}

std::vector<std::shared_ptr<TypeSignature>>* FunctionTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

bool FunctionTypeSignature::doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    return _parameterList->matchesWithArgumentList(argumentListTypeSignature);
}

std::shared_ptr<TypeSignature> FunctionTypeSignature::getReturnType() {
    return _returnType;
}

std::string FunctionTypeSignature::toDetailString() {
    return _parameterList->toDetailString();
}

std::string FunctionTypeSignature::toString() {
    return "FUNCTION_TYPE_SIGNATURE";
}

TypeSource FunctionTypeSignature::getTypeSource() {
    return FUNCTION_TYPE_SOURCE;
}

std::shared_ptr<TypeSignature> FunctionTypeSignature::getTargetTypeSignature() {
    return _returnType;
}

bool FunctionTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<FunctionTypeSignature>(otherType);
    return this->getParameterList()->isEqualTo(other->getParameterList()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}

void FunctionTypeSignature::copyFrom(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = std::dynamic_pointer_cast<FunctionTypeSignature>(otherType);
    _returnType = other->getReturnType();
    _parameterList = other->getParameterList();
}

bool FunctionTypeSignature::hasVariableLengthParameters() {
    return _parameterList->isVariableLength();
}

uint64_t FunctionTypeSignature::getVariableLengthParametersStartIndex() {
    return _parameterList->getVariableLengthStartIndex();
}

void FunctionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}