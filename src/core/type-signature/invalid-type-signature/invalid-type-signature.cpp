//
// Created by Johny Georges on 2024-05-07.
//

#include "invalid-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

std::string InvalidTypeSignature::toDetailString() {
    return "jet.invalid";
}

std::string InvalidTypeSignature::toString() {
    return "INVALID_TYPE_SIGNATURE";
}

TypeSource InvalidTypeSignature::getTypeSource() {
    return INVALID_TYPE_SOURCE;
}

bool InvalidTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void InvalidTypeSignature::print() {
    Logger::log(this->toString());
}