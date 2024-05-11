//
// Created by Johny Georges on 2024-05-11.
//

#include "literal-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

bool LiteralTypeSignature::isLiteral() {
    return true;
}

std::string LiteralTypeSignature::toString() {
    return "LITERAL_TYPE_SIGNATURE";
}

TypeSource LiteralTypeSignature::getTypeSource() {
    return LITERAL_TYPE_SOURCE;
}

bool LiteralTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void LiteralTypeSignature::print() {
    Logger::log(this->toString());
}