//
// Created by Johny Georges on 2024-05-18.
//

#include "lambda-expression-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature(ParameterListTypeSignature* parameterList, std::optional<TypeSignature*> returnType) {
    _parameterList = parameterList;
    _returnType = returnType;
}

ParameterListTypeSignature* LambdaExpressionTypeSignature::getParameterTypes() {
    return _parameterList;
}

std::optional<TypeSignature*> LambdaExpressionTypeSignature::getReturnType() {
    return _returnType;
}

std::string LambdaExpressionTypeSignature::toString() {
    return "LAMBDA_EXPRESSION_TYPE_SIGNATURE";
}

TypeSource LambdaExpressionTypeSignature::getTypeSource() {
    return LAMBDA_EXPRESSION_TYPE_SOURCE;
}

bool LambdaExpressionTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (LambdaExpressionTypeSignature*)otherType;

    if (!_returnType.has_value() && other->getReturnType().has_value() ||
        _returnType.has_value() && !other->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && other->getReturnType().has_value() &&
        !_returnType.value()->isEqualTo(other->getReturnType().value())) {
        return false;
    }

    return this->getParameterTypes()->isEqualTo(other->getParameterTypes());
}

void LambdaExpressionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    Logger::log("----------");
}