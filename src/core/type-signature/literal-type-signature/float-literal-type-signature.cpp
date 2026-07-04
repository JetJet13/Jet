//
// Created by Johny Georges on 2024-05-06.
//

#include "float-literal-type-signature.h"

std::shared_ptr<LiteralTypeSignature> FloatLiteralTypeSignature::clone() {
    return std::make_shared<FloatLiteralTypeSignature>();
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

bool FloatLiteralTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->isEqualTo(otherType);
}