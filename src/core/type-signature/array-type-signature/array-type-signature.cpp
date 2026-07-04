//
// Created by Johny Georges on 2024-04-30.
//

#include "array-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

ArrayTypeSignature::ArrayTypeSignature() {
    _elementType = std::make_shared<UnknownTypeSignature>();
}

ArrayTypeSignature::ArrayTypeSignature(std::shared_ptr<TypeSignature> elementType) {
    _elementType = elementType;
}

std::shared_ptr<TypeSignature> ArrayTypeSignature::getElementType() {
    return _elementType;
}

void ArrayTypeSignature::setElementType(std::shared_ptr<TypeSignature> elementType) {
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

bool ArrayTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ArrayTypeSignature>(otherType);
    return this->getElementType()->isEqualTo(other->getElementType());
}

void ArrayTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("----------");
}