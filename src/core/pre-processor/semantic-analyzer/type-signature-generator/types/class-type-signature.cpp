//
// Created by Johny Georges on 2024-04-30.
//

#include "class-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

ClassTypeSignature::ClassTypeSignature(Lexeme* className) {
    _className = className;
}

Lexeme* ClassTypeSignature::getName() {
    return _className;
}

std::string ClassTypeSignature::toString() {
    return "CLASS_TYPE_SIGNATURE";
}

TypeSource ClassTypeSignature::getTypeSource() {
    return CLASS_TYPE_SOURCE;
}

bool ClassTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() == otherType->getTypeSource()) {
        return this->getName()->isEqualTo(((ClassTypeSignature*)otherType)->getName());
    }

    return false;
}

void ClassTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    // todo: add class name print log;
    Logger::log("----------");
}