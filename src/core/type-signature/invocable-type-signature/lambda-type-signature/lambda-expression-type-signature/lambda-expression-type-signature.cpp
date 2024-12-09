//
// Created by Johny Georges on 2024-05-18.
//

#include "lambda-expression-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../void-type-signature/void-type-signature.h"

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature() {
    _parameterList = new ParameterListTypeSignature();
    _scopeParameter = ParameterListItemTypeSignature::createScopeParameter();
    _returnType = new VoidTypeSignature();
}

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature(ParameterListTypeSignature* parameterList, ParameterListItemTypeSignature* scopeParameter, std::optional<TypeSignature*> returnType) {
    _parameterList = parameterList;
    _scopeParameter = scopeParameter;
    if (returnType) {
        _returnType = returnType.value();
    } else {
        _returnType = new VoidTypeSignature();
    }
}

ParameterListItemTypeSignature* LambdaExpressionTypeSignature::getScopeParameter() {
    return _scopeParameter;
}

bool LambdaExpressionTypeSignature::isScopeParameterNecessary() {
    return !((StructTypeSignature*)_scopeParameter->getTypeSignature())->isEmpty();
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
           this->getScopeParameter()->isEqualTo(other->getScopeParameter()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}

void LambdaExpressionTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _scopeParameter->print();
    _returnType->print();
    Logger::log("----------");
}