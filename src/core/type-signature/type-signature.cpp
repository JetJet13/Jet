//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature.h"

bool TypeSignature::hasTypeSource(TypeSource other) {
    return this->getTypeSource() == other;
}

bool TypeSignature::isUnknown() {
    return this->getTypeSource() == UNKNOWN_TYPE_SOURCE;
}

bool TypeSignature::isInvalid() {
    return this->getTypeSource() == INVALID_TYPE_SOURCE;
}

bool TypeSignature::isVoid() {
    return this->getTypeSource() == VOID_TYPE_SOURCE;
}