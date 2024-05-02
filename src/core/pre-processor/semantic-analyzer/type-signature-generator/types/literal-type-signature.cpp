//
// Created by Johny Georges on 2024-04-30.
//

#include "literal-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"


LiteralTypeSignature::LiteralTypeSignature(Type type) {
    _coreType = type;
}

Type LiteralTypeSignature::getType() {
    return _coreType;
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
    Logger::log("CORE_TYPE - ", _coreType);
    Logger::log("----------");
}