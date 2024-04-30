//
// Created by Johny Georges on 2024-04-30.
//

#include "tuple-type.h"

TupleType::TupleType(std::vector<BaseType*>* elementTypes) {
    _elementTypes = elementTypes;
}

std::vector<BaseType*>* TupleType::getElementTypes() {
    return _elementTypes;
}

TypeSource TupleType::getTypeSource() {
    return TUPLE_TYPE_SOURCE;
}

bool TupleType::isEqualTo(BaseType* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (TupleType*)otherType;
    for (int i = 0; i < _elementTypes->size(); ++i) {
        if (!_elementTypes->at(i)->isEqualTo(other->getElementTypes()->at(i))) {
            return false;
        }
    }

    return true;
}