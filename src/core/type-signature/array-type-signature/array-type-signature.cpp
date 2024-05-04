//
// Created by Johny Georges on 2024-04-30.
//

#include "array-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ArrayTypeSignature::ArrayTypeSignature(TypeSignature* elementType, unsigned long size) {
    _elementType = elementType;
    _size = size;
}

TypeSignature* ArrayTypeSignature::getElementType() {
    return _elementType;
}

unsigned long ArrayTypeSignature::getSize() {
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
    return this->getElementType()->isEqualTo(other->getElementType()) &&
           this->getSize() == other->getSize();
}

void ArrayTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("SIZE - ", _size);
    Logger::log("----------");
}