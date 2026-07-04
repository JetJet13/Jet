//
// Created by Johny Georges on 2024-05-06.
//

#include "char-literal-type-signature.h"

std::shared_ptr<LiteralTypeSignature> CharLiteralTypeSignature::clone() {
    return std::make_shared<CharLiteralTypeSignature>();
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

bool CharLiteralTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->isEqualTo(otherType);
}