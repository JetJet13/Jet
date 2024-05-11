//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature.h"

bool TypeSignature::is(TypeSource other) {
    return this->getTypeSource() == other;
}

bool TypeSignature::isOneOf(std::vector<TypeSource> typeSources) {
    return std::find(
            typeSources.begin(),
            typeSources.end(),
            this->getTypeSource()) != typeSources.end();
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

bool TypeSignature::isUnknownOrInvalidOrVoid() {
    return this->isUnknown() ||
           this->isInvalid() ||
           this->isVoid();
}

bool TypeSignature::isLiteral() {
    return false;
}