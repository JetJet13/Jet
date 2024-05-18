//
// Created by Johny Georges on 2024-05-09.
//

#include "lambda-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

LambdaTypeSignature::LambdaTypeSignature(std::vector<TypeSignature*>* parameterTypes, std::optional<TypeSignature*> returnType) {
    _parameterTypes = parameterTypes;
    _returnType = returnType;
}

LambdaTypeSignature::LambdaTypeSignature(std::vector<TypeSignature*> parameterTypes, std::optional<TypeSignature*> returnType) {
    _parameterTypes = new std::vector<TypeSignature*>();
    for (auto parameter : parameterTypes) {
        _parameterTypes->push_back(parameter);
    }
    _returnType = returnType;
}

std::vector<TypeSignature*>* LambdaTypeSignature::getParameterTypes() {
    return _parameterTypes;
}

std::optional<TypeSignature*> LambdaTypeSignature::getReturnType() {
    return _returnType;
}

std::string LambdaTypeSignature::toString() {
    return "LAMBDA_TYPE_SIGNATURE";
}

TypeSource LambdaTypeSignature::getTypeSource() {
    return LAMBDA_TYPE_SOURCE;
}

bool LambdaTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (LambdaTypeSignature*)otherType;

    if (!_returnType.has_value() && other->getReturnType().has_value() ||
        _returnType.has_value() && !other->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && other->getReturnType().has_value() &&
        !_returnType.value()->isEqualTo(other->getReturnType().value())) {
        return false;
    }

    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }
    return true;
}

void LambdaTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        _parameterTypes->at(i)->print();
    }
    if (_returnType) {
        _returnType.value()->print();
    }
    Logger::log("----------");
}