//
// Created by Johny Georges on 2024-05-18.
//

#include "lambda-expression-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../void-type-signature/void-type-signature.h"

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature() {
    _parameterList = std::make_shared<ParameterListTypeSignature>();
    _scopeParameter = ParameterListItemTypeSignature::createScopeParameter();
    _returnType = std::make_shared<VoidTypeSignature>();
}

LambdaExpressionTypeSignature::LambdaExpressionTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList, std::shared_ptr<ParameterListItemTypeSignature> scopeParameter, std::optional<std::shared_ptr<TypeSignature>> returnType) {
    _parameterList = parameterList;
    _scopeParameter = scopeParameter;
    if (returnType) {
        _returnType = returnType.value();
    } else {
        _returnType = std::make_shared<VoidTypeSignature>();
    }
}

std::shared_ptr<ParameterListItemTypeSignature> LambdaExpressionTypeSignature::getScopeParameter() {
    return _scopeParameter;
}

bool LambdaExpressionTypeSignature::isScopeParameterNecessary() {
    return !(std::dynamic_pointer_cast<LambdaScopeTypeSignature>(_scopeParameter->getTypeSignature())->isEmpty());
}

std::shared_ptr<ParameterListTypeSignature> LambdaExpressionTypeSignature::getParameterList() {
    return _parameterList;
}

bool LambdaExpressionTypeSignature::hasScopeArgument() {
    return true;
}

std::vector<std::shared_ptr<TypeSignature>>* LambdaExpressionTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

bool LambdaExpressionTypeSignature::doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    return _parameterList->matchesWithArgumentList(argumentListTypeSignature);
}

std::shared_ptr<TypeSignature> LambdaExpressionTypeSignature::getReturnType() {
    return _returnType;
}

std::string LambdaExpressionTypeSignature::toDetailString() {
    return _parameterList->toDetailString();
}

std::string LambdaExpressionTypeSignature::toString() {
    return "LAMBDA_EXPRESSION_TYPE_SIGNATURE";
}

TypeSource LambdaExpressionTypeSignature::getTypeSource() {
    return LAMBDA_EXPRESSION_TYPE_SOURCE;
}

bool LambdaExpressionTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<LambdaExpressionTypeSignature>(otherType);
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