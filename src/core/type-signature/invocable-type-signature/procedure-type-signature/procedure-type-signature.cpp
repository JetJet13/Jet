//
// Created by Johny Georges on 2024-04-30.
//

#include "procedure-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../struct-type-signature/struct-type-signature.h"

ProcedureTypeSignature::ProcedureTypeSignature() {
    _parameterList = std::make_shared<ParameterListTypeSignature>();
}

ProcedureTypeSignature::ProcedureTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList) {
    _parameterList = parameterList;
}

std::shared_ptr<ParameterListTypeSignature> ProcedureTypeSignature::getParameterList() {
    return _parameterList;
}


std::vector<std::shared_ptr<TypeSignature>>* ProcedureTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

bool ProcedureTypeSignature::doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    return _parameterList->matchesWithArgumentList(argumentListTypeSignature);
}

std::shared_ptr<TypeSignature> ProcedureTypeSignature::getReturnType() {
    return _returnType;
}

std::string ProcedureTypeSignature::toDetailString() {
    return _parameterList->toDetailString();
}

std::string ProcedureTypeSignature::toString() {
    return "PROCEDURE_TYPE_SIGNATURE";
}

TypeSource ProcedureTypeSignature::getTypeSource() {
    return PROCEDURE_TYPE_SOURCE;
}

std::shared_ptr<TypeSignature> ProcedureTypeSignature::getTargetTypeSignature() {
    return _returnType;
}

bool ProcedureTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ProcedureTypeSignature>(otherType);
    return this->getParameterList()->isEqualTo(other->getParameterList());
}

void ProcedureTypeSignature::copyFrom(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = std::dynamic_pointer_cast<ProcedureTypeSignature>(otherType);
    _parameterList = other->getParameterList();
}

bool ProcedureTypeSignature::hasVariableLengthParameters() {
    return _parameterList->isVariableLength();
}

uint64_t ProcedureTypeSignature::getVariableLengthParametersStartIndex() {
    return _parameterList->getVariableLengthStartIndex();
}

void ProcedureTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    Logger::log("----------");
}