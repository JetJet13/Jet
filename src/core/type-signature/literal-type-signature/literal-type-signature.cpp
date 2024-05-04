//
// Created by Johny Georges on 2024-04-30.
//

#include "literal-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


LiteralTypeSignature::LiteralTypeSignature(LiteralType type) {
    _type = type;
}

LiteralType LiteralTypeSignature::getType() {
    return _type;
}

std::string LiteralTypeSignature::toString() {
    return "LITERAL_TYPE_SIGNATURE";
}

TypeSource LiteralTypeSignature::getTypeSource() {
    return LITERAL_TYPE_SOURCE;
}

bool LiteralTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() == otherType->getTypeSource()) {
        return this->getType() == ((LiteralTypeSignature*)otherType)->getType();
    }

    return false;
}

void LiteralTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("LITERAL_TYPE - ", _type);
    Logger::log("----------");
}