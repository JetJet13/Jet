//
// Created by Johny Georges on 2024-05-06.
//

#include "int-literal-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


std::string IntLiteralTypeSignature::toString() {
    return "INT_LITERAL_TYPE_SIGNATURE";
}

TypeSource IntLiteralTypeSignature::getTypeSource() {
    return INT_LITERAL_TYPE_SOURCE;
}

bool IntLiteralTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void IntLiteralTypeSignature::print() {
    Logger::log(this->toString());
}