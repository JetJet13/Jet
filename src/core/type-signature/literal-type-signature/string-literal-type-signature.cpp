//
// Created by Johny Georges on 2024-05-06.
//

#include "string-literal-type-signature.h"

std::shared_ptr<LiteralTypeSignature> StringLiteralTypeSignature::clone() {
    return std::make_shared<StringLiteralTypeSignature>();
}

std::string StringLiteralTypeSignature::toDetailString() {
    return "string";
}

std::string StringLiteralTypeSignature::toString() {
    return "STRING_LITERAL_TYPE_SIGNATURE";
}

TypeSource StringLiteralTypeSignature::getTypeSource() {
    return STRING_LITERAL_TYPE_SOURCE;
}

bool StringLiteralTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->isEqualTo(otherType);
}