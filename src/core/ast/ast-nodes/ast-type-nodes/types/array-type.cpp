//
// Created by Johny Georges on 2024-04-30.
//

#include "array-type.h"

ArrayType::ArrayType(BaseType* elementType, int size) {
    _elementType = elementType;
    _size = size;
}

BaseType* ArrayType::getElementType() {
    return _elementType;
}

int ArrayType::getSize() {
    return _size;
}

TypeSource ArrayType::getTypeSource() {
    return ARRAY_TYPE_SOURCE;
}

bool ArrayType::isEqualTo(BaseType* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ArrayType*)otherType;
    return _elementType->isEqualTo(other->getElementType()) &&
           _size == other->getSize();
}