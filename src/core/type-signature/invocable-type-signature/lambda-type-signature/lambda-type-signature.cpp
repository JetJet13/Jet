//
// Created by Johny Georges on 2025-07-12.
//

#include "lambda-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

LambdaTypeSignature::LambdaTypeSignature() {
    _parameterTypes = {};
    _returnType = new VoidTypeSignature();
}

LambdaTypeSignature::LambdaTypeSignature(std::vector<TypeSignature*> parameterTypes, std::optional<TypeSignature*> returnType) {
    _parameterTypes = parameterTypes;
    _returnType = returnType.value_or(new VoidTypeSignature());
}

int LambdaTypeSignature::numParameters() {
    return _parameterTypes.size();
}

std::vector<TypeSignature*>* LambdaTypeSignature::getParameterTypes() {
    return &_parameterTypes;
}

bool LambdaTypeSignature::doArgumentsMatchParameters(ArgumentListTypeSignature* argumentListTypeSignature) {
    if (this->numParameters() != argumentListTypeSignature->numParameters()) {
        return false;
    }

    for (int i = 0; i < this->numParameters(); ++i) {
        auto parameter = _parameterTypes[i];
        auto argument = argumentListTypeSignature->getArgumentTypes()->at(i);
        if (!parameter->isEquivalentTo(argument)) {
            return false;
        }
    }
    return true;
}

TypeSignature* LambdaTypeSignature::getReturnType() {
    return _returnType;
}

std::string LambdaTypeSignature::toDetailString() {
    std::string detailString = "jet.lambda.";
    for (auto type : _parameterTypes) {
        detailString += "_" + type->toDetailString();
    }
    return detailString;
}

std::string LambdaTypeSignature::toString() {
    return "LAMBDA_TYPE_SIGNATURE";
}

TypeSource LambdaTypeSignature::getTypeSource() {
    return LAMBDA_TYPE_SOURCE;
}

TypeSignature* LambdaTypeSignature::convertToVariableTypeSignature() {
    return this;
}

bool LambdaTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (LambdaTypeSignature*)otherType;
    auto otherParameters = other->getParameterTypes();
    if (this->numParameters() != other->numParameters()) {
        return false;
    }
    for (int i = 0; i < this->numParameters(); i++) {
        if (!_parameterTypes[i]->isEqualTo(otherParameters->at(i))) {
            return false;
        }
    }

    return this->getReturnType()->isEqualTo(other->getReturnType());
}


void LambdaTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameterType : _parameterTypes) {
        parameterType->print();
    }
    _returnType->print();
    Logger::log("----------");
}