//
// Created by Johny Georges on 2024-05-07.
//

#include "not-null-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

std::string NotNullTypeSignature::toDetailString() {
    return "jet.not_null";
}

std::string NotNullTypeSignature::toString() {
    return "NOT_NULL_TYPE_SIGNATURE";
}

TypeSource NotNullTypeSignature::getTypeSource() {
    return NOT_NULL_TYPE_SOURCE;
}

bool NotNullTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void NotNullTypeSignature::print() {
    Logger::log(this->toString());
}