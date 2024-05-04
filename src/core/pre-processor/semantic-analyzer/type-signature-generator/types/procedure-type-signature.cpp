//
// Created by Johny Georges on 2024-04-30.
//

#include "procedure-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

ProcedureTypeSignature::ProcedureTypeSignature(std::string name, ParameterListTypeSignature* parameterList) {
    _name = name;
    _parameterList = parameterList;
}

std::string ProcedureTypeSignature::getName() {
    return _name;
}

ParameterListTypeSignature* ProcedureTypeSignature::getParameterList() {
    return _parameterList;
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
    return this->getName() == other->getName() &&
           this->getParameterList()->isEqualTo(other->getParameterList());
}

void ProcedureTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _parameterList->print();
    Logger::log("----------");
}