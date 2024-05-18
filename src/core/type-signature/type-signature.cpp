//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature.h"

bool TypeSignature::is(TypeSource other) {
    return this->getTypeTarget() == other;
}

bool TypeSignature::isOneOf(std::vector<TypeSource> typeSources) {
    return std::find(
            typeSources.begin(),
            typeSources.end(),
            this->getTypeTarget()) != typeSources.end();
}

bool TypeSignature::isUnknown() {
    return this->getTypeTarget() == UNKNOWN_TYPE_SOURCE;
}

bool TypeSignature::isInvalid() {
    return this->getTypeTarget() == INVALID_TYPE_SOURCE;
}

bool TypeSignature::isVoid() {
    return this->getTypeTarget() == VOID_TYPE_SOURCE;
}

bool TypeSignature::isUnknownOrInvalidOrVoid() {
    return this->isUnknown() ||
           this->isInvalid() ||
           this->isVoid();
}

bool TypeSignature::isLiteral() {
    return false;
}

void TypeSignature::copyFrom(TypeSignature* otherType) {}

TypeSource TypeSignature::getTypeTarget() {
    return this->getTypeSource();
}