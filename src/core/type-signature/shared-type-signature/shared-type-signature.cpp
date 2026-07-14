//
// Created by Johny Georges on 2026-07-11.
//

#include "shared-type-signature.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

SharedTypeSignature::SharedTypeSignature() {
    _underlyingType = std::make_shared<UnknownTypeSignature>();
}

SharedTypeSignature::SharedTypeSignature(std::shared_ptr<TypeSignature> underlyingType) {
    _underlyingType = underlyingType;
}

std::shared_ptr<TypeSignature> SharedTypeSignature::getUnderlyingType() {
    return _underlyingType;
}

std::string SharedTypeSignature::toDetailString() {
    return "shared." + _underlyingType->toDetailString();
}

std::string SharedTypeSignature::toString() {
    return "SHARE_TYPE_SIGNATURE";
}

TypeSource SharedTypeSignature::getTypeSource() {
    return SHARED_TYPE_SOURCE;
}

bool SharedTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<SharedTypeSignature>(otherType);
    return this->_underlyingType->isEqualTo(other->getUnderlyingType());
}

bool SharedTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<SharedTypeSignature>(otherType);
    return this->_underlyingType->isEquivalentTo(other->getUnderlyingType());
}

void SharedTypeSignature::print() {
    Logger::log(this->toString(), "(");
    this->_underlyingType->print();
    Logger::log(")");
}