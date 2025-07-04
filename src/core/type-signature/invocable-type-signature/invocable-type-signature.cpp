//
// Created by Johny Georges on 2024-06-08.
//

#include "invocable-type-signature.h"
#include "lambda-type-signature/procedure-lambda-type-signature/procedure-lambda-type-signature.h"
#include "lambda-type-signature/function-lambda-type-signature/function-lambda-type-signature.h"

bool InvocableTypeSignature::isInvocable() {
    return true;
}

bool InvocableTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (!otherType->isInvocable()) {
        return false;
    }

    auto other = (InvocableTypeSignature*)otherType;
    if (!this->getReturnType()->isEquivalentTo(other->getReturnType())) {
        return false;
    }

    if (this->getParameterTypes()->size() != other->getParameterTypes()->size()) {
        return false;
    }

    for (int i = 0; i < this->getParameterTypes()->size(); ++i) {
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
    if (this->getReturnType()->isVoid()) {
        return new ProcedureLambdaTypeSignature(parameterTypes);
    }
    return new FunctionLambdaTypeSignature(parameterTypes, this->getReturnType()->convertToVariableTypeSignature());
}