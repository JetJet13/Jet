//
// Created by Johny Georges on 2024-05-06.
//

#include "bool-literal-type-signature.h"

LiteralTypeSignature* BoolLiteralTypeSignature::clone() {
    return new BoolLiteralTypeSignature();
}

std::string BoolLiteralTypeSignature::toDetailString() {
    return "bool";
}

std::string BoolLiteralTypeSignature::toString() {
    return "BOOL_LITERAL_TYPE_SIGNATURE";
}

TypeSource BoolLiteralTypeSignature::getTypeSource() {
    return BOOL_LITERAL_TYPE_SOURCE;
}

bool BoolLiteralTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    return this->isEqualTo(otherType);
}