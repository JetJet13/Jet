//
// Created by Johny Georges on 2024-05-07.
//

#include "void-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


std::string VoidTypeSignature::toDetailString() {
    return "jet.void";
}

std::string VoidTypeSignature::toString() {
    return "VOID_TYPE_SIGNATURE";
}

TypeSource VoidTypeSignature::getTypeSource() {
    return VOID_TYPE_SOURCE;
}

bool VoidTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void VoidTypeSignature::print() {
    Logger::log(this->toString());
}