//
// Created by Johny Georges on 2024-05-06.
//

#include "float-literal-type-signature.h"

LiteralTypeSignature* FloatLiteralTypeSignature::clone() {
    return new FloatLiteralTypeSignature();
}

std::string FloatLiteralTypeSignature::toDetailString() {
    return "float";
}

std::string FloatLiteralTypeSignature::toString() {
    return "FLOAT_LITERAL_TYPE_SIGNATURE";
}

TypeSource FloatLiteralTypeSignature::getTypeSource() {
    return FLOAT_LITERAL_TYPE_SOURCE;
}

bool FloatLiteralTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    return this->isEqualTo(otherType);
}