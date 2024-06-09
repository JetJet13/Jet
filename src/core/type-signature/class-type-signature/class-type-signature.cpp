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

ClassTypeSignature* ClassTypeSignature::addConstructor(std::string key, ClassConstructorTypeSignature* classConstructorTypeSignature) {
    _constructors.insert(key, classConstructorTypeSignature);
    return this;
}

ClassTypeSignature* ClassTypeSignature::addProperty(std::string key, ClassPropertyTypeSignature* classPropertyTypeSignature) {
    _properties.insert(key, classPropertyTypeSignature);
    return this;
}

ClassTypeSignature* ClassTypeSignature::addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature) {
    _methods.insert(key, classMethodTypeSignature);
    return this;
}

std::string ClassTypeSignature::toString() {
    return "CLASS_TYPE_SIGNATURE";
}

TypeSource ClassTypeSignature::getTypeSource() {
    return CLASS_TYPE_SOURCE;
}

bool ClassTypeSignature::isEqualTo(TypeSignature* otherType) {
    // todo: figure out an elegant way to perform equality check
    // for class type-signatures without causing an infinite loop
    // due to class instance references of self.
    return this->getTypeSource() == otherType->getTypeSource();
}

void ClassTypeSignature::copyFrom(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = (ClassTypeSignature*)otherType;
    _properties = *other->getProperties();
    _constructors = *other->getConstructors();
    _methods = *other->getMethods();
}

void ClassTypeSignature::print() {
    Logger::log(this->toString());
}