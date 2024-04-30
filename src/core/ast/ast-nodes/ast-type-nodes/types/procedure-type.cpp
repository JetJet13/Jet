//
// Created by Johny Georges on 2024-04-30.
//

#include "procedure-type.h"

ProcedureType::ProcedureType(std::vector<BaseType*>* parameterTypes) {
    _parameterTypes = parameterTypes;
}

std::vector<BaseType*>* ProcedureType::getParameterTypes() {
    return _parameterTypes;
}

TypeSource ProcedureType::getTypeSource() {
    return PROCEDURE_TYPE_SOURCE;
}

bool ProcedureType::isEqualTo(BaseType* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ProcedureType*)otherType;
    for (int i = 0; i < _parameterTypes->size(); ++i) {
        if (!_parameterTypes->at(i)->isEqualTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }

    return true;
}