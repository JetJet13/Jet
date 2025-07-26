//
// Created by Johny Georges on 2024-04-30.
//

#include "procedure-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../struct-type-signature/struct-type-signature.h"

ProcedureTypeSignature::ProcedureTypeSignature() {
    _parameterList = new ParameterListTypeSignature();
}

ProcedureTypeSignature::ProcedureTypeSignature(ParameterListTypeSignature* parameterList) {
    _parameterList = parameterList;
}

ParameterListTypeSignature* ProcedureTypeSignature::getParameterList() {
    return _parameterList;
}


std::vector<TypeSignature*>* ProcedureTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

TypeSignature* ProcedureTypeSignature::getReturnType() {
    return _returnType;
}

std::string ProcedureTypeSignature::toString() {
    return "PROCEDURE_TYPE_SIGNATURE";
}

TypeSource ProcedureTypeSignature::getTypeSource() {
    return PROCEDURE_TYPE_SOURCE;
}

TypeSignature* ProcedureTypeSignature::getTargetTypeSignature() {
    return _returnType;
}

bool ProcedureTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ProcedureTypeSignature*)otherType;
    return this->getParameterList()->isEqualTo(other->getParameterList());
}

void ProcedureTypeSignature::copyFrom(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = (ProcedureTypeSignature*)otherType;
    _parameterList = other->getParameterList();
}

bool ProcedureTypeSignature::hasVariableLengthParameters() {
    return _parameterList->isVariableLength();
}

unsigned long ProcedureTypeSignature::getVariableLengthParametersStartIndex() {
    return _parameterList->getVariableLengthStartIndex();
}

void ProcedureTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    Logger::log("----------");
}