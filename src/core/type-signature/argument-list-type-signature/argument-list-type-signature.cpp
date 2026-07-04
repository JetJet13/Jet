//
// Created by Johny Georges on 2024-12-31.
//

#include "argument-list-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ArgumentListTypeSignature::ArgumentListTypeSignature() {
    _argumentTypes = std::vector<std::shared_ptr<TypeSignature>>();
}

ArgumentListTypeSignature::ArgumentListTypeSignature(std::vector<std::shared_ptr<TypeSignature>> argumentTypes) {
    _argumentTypes = argumentTypes;
}

std::vector<std::shared_ptr<TypeSignature>>* ArgumentListTypeSignature::getArgumentTypes() {
    return &_argumentTypes;
}

unsigned long ArgumentListTypeSignature::numParameters() {
    return _argumentTypes.size();
}

std::string ArgumentListTypeSignature::toDetailString() {
    std::string detailString;
    for (auto argument : _argumentTypes) {
        detailString += "_" + argument->toDetailString();
    }
    return detailString;
}

std::string ArgumentListTypeSignature::toString() {
    return "ARGUMENT_LIST_TYPE_SIGNATURE";
}

TypeSource ArgumentListTypeSignature::getTypeSource() {
    return ARGUMENT_LIST_TYPE_SOURCE;
}

bool ArgumentListTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ArgumentListTypeSignature>(otherType);
    auto otherArgumentTypes = other->getArgumentTypes();
    if (this->numParameters() != other->numParameters()) {
        return false;
    }

    for (unsigned long i = 0; i < this->numParameters(); i++) {
        if (!_argumentTypes[i]->isEqualTo(otherArgumentTypes->at(i))) {
            return false;
        }
    }

    return true;
}

void ArgumentListTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto argument : _argumentTypes) {
        argument->print();
    }
    Logger::log("----------");
}