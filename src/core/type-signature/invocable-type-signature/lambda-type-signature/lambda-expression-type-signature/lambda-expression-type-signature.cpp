//
// Created by Johny Georges on 2024-05-18.
//

#include "lambda-expression-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../void-type-signature/void-type-signature.h"

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature() {
    _parameterList = new ParameterListTypeSignature();
    _returnType = new VoidTypeSignature();
}

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature(ParameterListTypeSignature* parameterList, std::optional<TypeSignature*> returnType) {
    _parameterList = parameterList;
    if (returnType) {
        _returnType = returnType.value();
    } else {
        _returnType = new VoidTypeSignature();
    }
}

ParameterListTypeSignature* LambdaExpressionTypeSignature::getParameterList() {
    return _parameterList;
}

std::vector<TypeSignature*>* LambdaExpressionTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

TypeSignature* LambdaExpressionTypeSignature::getReturnType() {
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
    return this->getParameterList()->isEqualTo(other->getParameterList()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}

void LambdaExpressionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}