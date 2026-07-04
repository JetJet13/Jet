//
// Created by Johny Georges on 2024-05-06.
//

#include "int-literal-type-signature.h"

std::shared_ptr<LiteralTypeSignature> IntLiteralTypeSignature::clone() {
    return std::make_shared<IntLiteralTypeSignature>();
}

std::string IntLiteralTypeSignature::toDetailString() {
    return "int";
}

std::string IntLiteralTypeSignature::toString() {
    return "INT_LITERAL_TYPE_SIGNATURE";
}

TypeSource IntLiteralTypeSignature::getTypeSource() {
    return INT_LITERAL_TYPE_SOURCE;
}

bool IntLiteralTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->isEqualTo(otherType);
}
