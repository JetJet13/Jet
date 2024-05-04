//
// Created by Johny Georges on 2024-04-30.
//

#include <utility>
#include "class-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ClassTypeSignature::ClassTypeSignature(std::string name) {
    _name = std::move(name);
    _constructors = TypeSignatureMap<ClassConstructorTypeSignature>();
    _properties = TypeSignatureMap<ClassPropertyTypeSignature>();
    _methods = TypeSignatureMap<ClassMethodTypeSignature>();
}

std::string ClassTypeSignature::getName() {
    return _name;
}

TypeSignatureMap<ClassConstructorTypeSignature>* ClassTypeSignature::getConstructors() {
    return &_constructors;
}

TypeSignatureMap<ClassPropertyTypeSignature>* ClassTypeSignature::getProperties() {
    return &_properties;
}

TypeSignatureMap<ClassMethodTypeSignature>* ClassTypeSignature::getMethods() {
    return &_methods;
}

std::string ClassTypeSignature::toString() {
    return "CLASS_TYPE_SIGNATURE";
}

TypeSource ClassTypeSignature::getTypeSource() {
    return CLASS_TYPE_SOURCE;
}

bool ClassTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ClassTypeSignature*)otherType;
    return this->getName() == other->getName() &&
           this->getProperties()->isEqualTo(other->getProperties()) &&
           this->getMethods()->isEqualTo(other->getMethods()) &&
           this->getConstructors()->isEqualTo(other->getConstructors());
}

void ClassTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    this->getProperties()->print();
    this->getMethods()->print();
    this->getConstructors()->print();
    Logger::log("----------");
}