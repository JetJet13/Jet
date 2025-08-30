//
// Created by Johny Georges on 2024-05-06.
//

#include "int-literal-type-signature.h"

std::string IntLiteralTypeSignature::toDetailString() {
    return "int";
}

std::string IntLiteralTypeSignature::toString() {
    return "INT_LITERAL_TYPE_SIGNATURE";
}

TypeSource IntLiteralTypeSignature::getTypeSource() {
    return INT_LITERAL_TYPE_SOURCE;
}

bool IntLiteralTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    return this->isEqualTo(otherType);
}
