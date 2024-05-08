//
// Created by Johny Georges on 2024-05-07.
//

#include "unknown-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

std::string UnknownTypeSignature::toString() {
    return "UNKNOWN_TYPE_SIGNATURE";
}

TypeSource UnknownTypeSignature::getTypeSource() {
    return UNKNOWN_TYPE_SOURCE;
}

bool UnknownTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void UnknownTypeSignature::print() {
    Logger::log(this->toString());
}