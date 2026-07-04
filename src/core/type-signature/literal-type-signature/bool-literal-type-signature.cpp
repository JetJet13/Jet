//
// Created by Johny Georges on 2024-05-06.
//

#include "bool-literal-type-signature.h"

std::shared_ptr<LiteralTypeSignature> BoolLiteralTypeSignature::clone() {
    return std::make_shared<BoolLiteralTypeSignature>();
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

bool BoolLiteralTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->isEqualTo(otherType);
}