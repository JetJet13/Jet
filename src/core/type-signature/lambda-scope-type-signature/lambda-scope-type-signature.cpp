//
// Created by Johny Georges on 2025-11-21.
//

#include "lambda-scope-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

LambdaScopeTypeSignature::LambdaScopeTypeSignature() {
    _capturedVariableIds = std::set<std::string>();
}

LambdaScopeTypeSignature::LambdaScopeTypeSignature(std::set<std::string>* capturedVariables) {
    _capturedVariableIds = *capturedVariables;
}

std::set<std::string>* LambdaScopeTypeSignature::getCapturedVariableIds() {
    return &_capturedVariableIds;
}

bool LambdaScopeTypeSignature::isEmpty() {
    return _capturedVariableIds.empty();
}

void LambdaScopeTypeSignature::addCapturedVariableId(std::string capturedVariableId) {
    _capturedVariableIds.insert(capturedVariableId);
}

std::string LambdaScopeTypeSignature::toDetailString() {
    return "jet.lambda.scope";
}

std::string LambdaScopeTypeSignature::toString() {
    return "LAMBDA_SCOPE_TYPE_SIGNATURE";
}

TypeSource LambdaScopeTypeSignature::getTypeSource() {
    return LAMBDA_SCOPE_TYPE_SOURCE;
}

bool LambdaScopeTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (LambdaScopeTypeSignature*)otherType;
    auto otherCapturedVariableIds = other->getCapturedVariableIds();
    if (otherCapturedVariableIds->size() != _capturedVariableIds.size()) {
        return false;
    }
    for (auto id : *otherCapturedVariableIds) {
        if (_capturedVariableIds.find(id) == _capturedVariableIds.end()) {
            return false;
        }
    }
    return true;
}

void LambdaScopeTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto capturedVariableId : _capturedVariableIds) {
        Logger::log("Captured Variable", capturedVariableId);
    }
    Logger::log("----------");
}