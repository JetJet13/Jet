//
// Created by Johny Georges on 2024-06-08.
//

#include "function-lambda-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

FunctionLambdaTypeSignature::FunctionLambdaTypeSignature(std::vector<TypeSignature*>* parameterTypes, TypeSignature* returnType) {
    _parameterTypes = parameterTypes;
    _returnType = returnType;
}

FunctionLambdaTypeSignature::FunctionLambdaTypeSignature(std::vector<TypeSignature*> parameterTypes, TypeSignature* returnType) {
    _parameterTypes = new std::vector<TypeSignature*>();
    for (auto parameter : parameterTypes) {
        _parameterTypes->push_back(parameter);
    }
    _returnType = returnType;
}

std::vector<TypeSignature*>* FunctionLambdaTypeSignature::getParameterTypes() {
    return _parameterTypes;
}

TypeSignature* FunctionLambdaTypeSignature::getReturnType() {
    return _returnType;
}

std::string FunctionLambdaTypeSignature::toString() {
    return "FUNCTION_LAMBDA_TYPE_SIGNATURE";
}

TypeSource FunctionLambdaTypeSignature::getTypeSource() {
    return FUNCTION_LAMBDA_TYPE_SOURCE;
}

TypeSignature* FunctionLambdaTypeSignature::getTargetTypeSignature() {
    return _returnType;
}

bool FunctionLambdaTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (FunctionLambdaTypeSignature*)otherType;
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }
    return _returnType->isEqualTo(other->getReturnType());
}

void FunctionLambdaTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto & _parameterType : *_parameterTypes) {
        _parameterType->print();
    }
    Logger::log("--RETURN TYPE--");
    _returnType->print();
    Logger::log("----------");
    Logger::log("----------");
}