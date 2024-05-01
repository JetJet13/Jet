//
// Created by Johny Georges on 2024-04-30.
//

#include "array-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

ArrayTypeSignature::ArrayTypeSignature(TypeSignature* elementType, int size) {
    _elementType = elementType;
    _size = size;
}

TypeSignature* ArrayTypeSignature::getElementType() {
    return _elementType;
}

int ArrayTypeSignature::getSize() {
    return _size;
}

std::string ArrayTypeSignature::toString() {
    return "ARRAY_TYPE_SIGNATURE";
}

TypeSource ArrayTypeSignature::getTypeSource() {
    return ARRAY_TYPE_SOURCE;
}

bool ArrayTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ArrayTypeSignature*)otherType;
    return _elementType->isEqualTo(other->getElementType()) &&
           _size == other->getSize();
}

void ArrayTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("SIZE - ", _size);
    Logger::log("----------");
}