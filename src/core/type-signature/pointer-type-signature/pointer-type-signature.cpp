//
// Created by Johny Georges on 2024-11-21.
//

#include "pointer-type-signature.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


PointerTypeSignature::PointerTypeSignature() {
    _underlyingType = new UnknownTypeSignature();
}

PointerTypeSignature::PointerTypeSignature(TypeSignature* underlyingType) {
    _underlyingType = underlyingType;
}

TypeSignature* PointerTypeSignature::getUnderlyingType() {
    return _underlyingType;
}

std::string PointerTypeSignature::toString() {
    return "POINTER_TYPE_SIGNATURE";
}

TypeSource PointerTypeSignature::getTypeSource() {
    return POINTER_TYPE_SOURCE;
}

TypeSource PointerTypeSignature::getTypeTarget() {
    return this->_underlyingType->getTypeTarget();
}

bool PointerTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = (PointerTypeSignature*)otherType;
    return this->_underlyingType->isEqualTo(other->getUnderlyingType());
}

bool PointerTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = (PointerTypeSignature*)otherType;
    return this->_underlyingType->isEquivalentTo(other->getUnderlyingType());
}

void PointerTypeSignature::print() {
    Logger::log(this->toString(), "(");
    this->_underlyingType->print();
    Logger::log(")");
}