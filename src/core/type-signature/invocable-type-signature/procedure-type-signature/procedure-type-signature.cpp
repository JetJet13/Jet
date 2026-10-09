// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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