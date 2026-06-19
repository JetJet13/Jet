//
// Created by Johny Georges on 2024-05-06.
//

#include "char-literal-type-signature.h"

LiteralTypeSignature* CharLiteralTypeSignature::clone() {
    return new CharLiteralTypeSignature();
}

std::string CharLiteralTypeSignature::toDetailString() {
    return "char";
}

std::string CharLiteralTypeSignature::toString() {
    return "CHAR_LITERAL_TYPE_SIGNATURE";
}

TypeSource CharLiteralTypeSignature::getTypeSource() {
    return CHAR_LITERAL_TYPE_SOURCE;
}

bool CharLiteralTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    return this->isEqualTo(otherType);
}