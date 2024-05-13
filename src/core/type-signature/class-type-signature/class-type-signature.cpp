//
// Created by Johny Georges on 2024-04-30.
//

#include <utility>
#include "class-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ClassTypeSignature::ClassTypeSignature() {
    _constructors = TypeSignatureMap<ClassConstructorTypeSignature>();
    _properties = TypeSignatureMap<ClassPropertyTypeSignature>();
    _methods = TypeSignatureMap<ClassMethodTypeSignature>();
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

void ClassTypeSignature::addConstructor(std::string key, ClassConstructorTypeSignature* classConstructorTypeSignature) {
    _constructors.insert(key, classConstructorTypeSignature);
}

void ClassTypeSignature::addProperty(std::string key, ClassPropertyTypeSignature* classPropertyTypeSignature) {
    _properties.insert(key, classPropertyTypeSignature);
}

void ClassTypeSignature::addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature) {
    _methods.insert(key, classMethodTypeSignature);
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
    return this->getProperties()->isEqualTo(other->getProperties()) &&
           this->getMethods()->isEqualTo(other->getMethods()) &&
           this->getConstructors()->isEqualTo(other->getConstructors());
}

void ClassTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getProperties()->print();
    this->getMethods()->print();
    this->getConstructors()->print();
    Logger::log("----------");
}