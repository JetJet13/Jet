//
// Created by Johny Georges on 2024-11-21.
//

#include "pointer-type-signature.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


PointerTypeSignature::PointerTypeSignature() {
    _underlyingType = std::make_shared<UnknownTypeSignature>();
}

PointerTypeSignature::PointerTypeSignature(std::shared_ptr<TypeSignature> underlyingType) {
    _underlyingType = underlyingType;
}

std::shared_ptr<TypeSignature> PointerTypeSignature::getUnderlyingType() {
    return _underlyingType;
}

std::string PointerTypeSignature::toDetailString() {
    return "jet.ptr." + _underlyingType->toDetailString();
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

bool PointerTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<PointerTypeSignature>(otherType);
    return this->_underlyingType->isEqualTo(other->getUnderlyingType());
}

bool PointerTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<PointerTypeSignature>(otherType);
    return this->_underlyingType->isEquivalentTo(other->getUnderlyingType());
}

void PointerTypeSignature::print() {
    Logger::log(this->toString(), "(");
    this->_underlyingType->print();
    Logger::log(")");
}