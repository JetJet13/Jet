//
// Created by Johny Georges on 2024-05-11.
//

#include "literal-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

std::shared_ptr<LiteralTypeSignature> LiteralTypeSignature::clone() {
    return std::make_shared<LiteralTypeSignature>();
}

bool LiteralTypeSignature::isLiteral() {
    return true;
}

std::string LiteralTypeSignature::toDetailString() {
    return "jet.literal";
}

std::string LiteralTypeSignature::toString() {
    return "LITERAL_TYPE_SIGNATURE";
}

TypeSource LiteralTypeSignature::getTypeSource() {
    return LITERAL_TYPE_SOURCE;
}

bool LiteralTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

bool LiteralTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType){
    return this->isLiteral() || this->getTypeSource() == otherType->getTypeSource();
}

void LiteralTypeSignature::print() {
    Logger::log(this->toString());
}