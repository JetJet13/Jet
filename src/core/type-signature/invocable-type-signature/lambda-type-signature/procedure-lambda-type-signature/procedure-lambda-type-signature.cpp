//
// Created by Johny Georges on 2024-06-08.
//

#include "procedure-lambda-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"


ProcedureLambdaTypeSignature::ProcedureLambdaTypeSignature(std::vector<TypeSignature*>* parameterTypes) {
    _parameterTypes = parameterTypes;
}

ProcedureLambdaTypeSignature::ProcedureLambdaTypeSignature(std::vector<TypeSignature*> parameterTypes) {
    _parameterTypes = new std::vector<TypeSignature*>();
    for (auto parameter : parameterTypes) {
        _parameterTypes->push_back(parameter);
    }
}

std::vector<TypeSignature*>* ProcedureLambdaTypeSignature::getParameterTypes() {
    return _parameterTypes;
}

TypeSignature* ProcedureLambdaTypeSignature::getReturnType() {
    return _returnType;
}

std::string ProcedureLambdaTypeSignature::toString() {
    return "PROCEDURE_LAMBDA_TYPE_SIGNATURE";
}

TypeSource ProcedureLambdaTypeSignature::getTypeSource() {
    return PROCEDURE_LAMBDA_TYPE_SOURCE;
}

TypeSignature* ProcedureLambdaTypeSignature::getTargetTypeSignature() {
    return _returnType;
}

bool ProcedureLambdaTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ProcedureLambdaTypeSignature*)otherType;
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }
    return true;
}

void ProcedureLambdaTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto & _parameterType : *_parameterTypes) {
        _parameterType->print();
    }
    Logger::log("----------");
}