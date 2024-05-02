//
// Created by Johny Georges on 2024-04-30.
//

#include "procedure-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

ProcedureTypeSignature::ProcedureTypeSignature(std::vector<TypeSignature*>* parameterTypes) {
    _parameterTypes = parameterTypes;
}

std::vector<TypeSignature*>* ProcedureTypeSignature::getParameterTypes() {
    return _parameterTypes;
}

std::string ProcedureTypeSignature::toString() {
    return "PROCEDURE_TYPE_SIGNATURE";
}

TypeSource ProcedureTypeSignature::getTypeSource() {
    return PROCEDURE_TYPE_SOURCE;
}

bool ProcedureTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ProcedureTypeSignature*)otherType;
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }

    return true;
}

void ProcedureTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        _parameterTypes->at(i)->print();
    }
    Logger::log("----------");
}