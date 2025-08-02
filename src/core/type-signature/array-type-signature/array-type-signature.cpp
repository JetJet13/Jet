//
// Created by Johny Georges on 2024-04-30.
//

#include "array-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

ArrayTypeSignature::ArrayTypeSignature() {
    _elementType = new UnknownTypeSignature();
}

ArrayTypeSignature::ArrayTypeSignature(TypeSignature* elementType) {
    _elementType = elementType;
}

TypeSignature* ArrayTypeSignature::getElementType() {
    return _elementType;
}

void ArrayTypeSignature::setElementType(TypeSignature* elementType) {
    _elementType = elementType;
}

std::string ArrayTypeSignature::toDetailString() {
    return "jet.arr." + _elementType->toDetailString();
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
    return this->getElementType()->isEqualTo(other->getElementType());
}

void ArrayTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("----------");
}