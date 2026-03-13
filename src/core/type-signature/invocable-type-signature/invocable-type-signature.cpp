//
// Created by Johny Georges on 2024-06-08.
//

#include "invocable-type-signature.h"
#include "lambda-type-signature/lambda-type-signature.h"

bool InvocableTypeSignature::isInvocable() {
    return true;
}

bool InvocableTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (_isGeneric && otherType->isInvocable()) {
        return true;
    } else if (!otherType->isInvocable()) {
        return false;
    }

    auto other = (InvocableTypeSignature*)otherType;
    if (!this->getReturnType()->isEquivalentTo(other->getReturnType())) {
        return false;
    }

    if (this->getParameterTypes()->size() != other->getParameterTypes()->size()) {
        return false;
    }

    for (unsigned long i = 0; i < this->getParameterTypes()->size(); ++i) {
        if (!this->getParameterTypes()->at(i)->isEquivalentTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }
    return true;
}

TypeSignature* InvocableTypeSignature::convertToVariableTypeSignature() {
    auto parameterTypes = std::vector<TypeSignature*>();
    for (auto parameter : *this->getParameterTypes()) {
        parameterTypes.push_back(parameter->convertToVariableTypeSignature());
    }
    return new LambdaTypeSignature(parameterTypes, this->getReturnType()->convertToVariableTypeSignature());
}

bool InvocableTypeSignature::isArgumentVarArg(int argumentIndex) {
    auto startIndex = this->getVariableLengthParametersStartIndex();
    return startIndex >= 0 && startIndex <= argumentIndex;
}

bool InvocableTypeSignature::hasScopeArgument() {
    return false;
}

bool InvocableTypeSignature::hasVariableLengthParameters() {
    return false;
}

unsigned long InvocableTypeSignature::getVariableLengthParametersStartIndex() {
    return -1;
}