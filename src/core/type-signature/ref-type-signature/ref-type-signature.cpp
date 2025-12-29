//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-type-signature.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


RefTypeSignature::RefTypeSignature() {
    _underlyingType = new UnknownTypeSignature();
}

RefTypeSignature::RefTypeSignature(TypeSignature* underlyingType) {
    _underlyingType = underlyingType;
}

TypeSignature* RefTypeSignature::getUnderlyingType() {
    return _underlyingType;
}

std::string RefTypeSignature::toDetailString() {
    return "ref." + _underlyingType->toDetailString();
}

std::string RefTypeSignature::toString() {
    return "REF_TYPE_SIGNATURE";
}

TypeSource RefTypeSignature::getTypeSource() {
    return REF_TYPE_SOURCE;
}

//TypeSource RefTypeSignature::getTypeTarget() {
//    return this->_underlyingType->getTypeTarget();
//}

bool RefTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = (RefTypeSignature*)otherType;
    return this->_underlyingType->isEqualTo(other->getUnderlyingType());
}

bool RefTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = (RefTypeSignature*)otherType;
    return this->_underlyingType->isEquivalentTo(other->getUnderlyingType());
}

void RefTypeSignature::print() {
    Logger::log(this->toString(), "(");
    this->_underlyingType->print();
    Logger::log(")");
}