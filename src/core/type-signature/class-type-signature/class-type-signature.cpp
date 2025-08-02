//
// Created by Johny Georges on 2024-04-30.
//

#include <utility>
#include "class-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "class-instance-type-signature/class-instance-type-signature.h"

ClassTypeSignature::ClassTypeSignature() {
    _constructors = TypeSignatureMap<ClassConstructorTypeSignature>();
    _properties = TypeSignatureMap<ClassPropertyTypeSignature>();
    _methods = TypeSignatureMap<ClassMethodTypeSignature>();
    _implements = TypeSignatureMap<TypeSignature>();
    _interface = TypeSignatureMap<TypeSignature>();
    _classScopeParameter = ParameterListItemTypeSignature::createClassScopeParameter();
}

ParameterListItemTypeSignature* ClassTypeSignature::getClassScopeParameter() {
    return _classScopeParameter;
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

TypeSignatureMap<TypeSignature>* ClassTypeSignature::getImplements() {
    return &_implements;
}

TypeSignatureMap<TypeSignature>* ClassTypeSignature::getInterface() {
    return &_interface;
}

ClassTypeSignature* ClassTypeSignature::addConstructor(std::string key, ClassConstructorTypeSignature* classConstructorTypeSignature) {
    _constructors.insert(key, classConstructorTypeSignature);
    return this;
}

ClassTypeSignature* ClassTypeSignature::addProperty(std::string key, ClassPropertyTypeSignature* classPropertyTypeSignature) {
    _properties.insert(key, classPropertyTypeSignature);
    if (classPropertyTypeSignature->getAccessModifier()->isPublic()) {
        auto interfaceKey = key;
        interfaceKey.erase(0, this->getId().size() + 1);
        _interface.insert(interfaceKey, classPropertyTypeSignature->convertToVariableTypeSignature());
    }
    return this;
}

ClassTypeSignature* ClassTypeSignature::addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature) {
    _methods.insert(key, classMethodTypeSignature);
    if (classMethodTypeSignature->getAccessModifier()->isPublic()) {
        auto interfaceKey = key;
        interfaceKey.erase(0, this->getId().size() + 1);
        _interface.insert(interfaceKey, classMethodTypeSignature->convertToVariableTypeSignature());
    }
    return this;
}

ClassTypeSignature* ClassTypeSignature::addImplementsInterface(std::string key, TypeSignature* interfaceTypeSignature) {
    _implements.insert(key, interfaceTypeSignature);
    return this;
}

void ClassTypeSignature::setClassScopeParameter(ParameterListItemTypeSignature* classScopeParameter) {
    _classScopeParameter = classScopeParameter;
}

bool ClassTypeSignature::isClassScopeParameterNecessary() {
    auto classScopeTypeSignature = (PointerTypeSignature*)_classScopeParameter->getTypeSignature();
    auto classScopeUnderlyingTypeSignature = (StructTypeSignature*)classScopeTypeSignature->getUnderlyingType();
    return !classScopeUnderlyingTypeSignature->isEmpty();
}

bool ClassTypeSignature::satisfiesImplementInterfaces() {
    for (auto interface : _implements.getValues()) {
        if (interface->typeSourceIs(INTERFACE_TYPE_SOURCE)) {
            auto interfaceTypeSignature = (InterfaceTypeSignature*)interface;
            if (!interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(&_interface)) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

std::string ClassTypeSignature::getPreConstructorName() {
    return this->getId() + ".pre.constructor";
}

std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> ClassTypeSignature::findConstructorForArguments(std::vector<TypeSignature*>* argumentTypeSignatures) {
    for (auto constructor : _constructors.getKeyValues()) {
        if (constructor.second->matchArguments(argumentTypeSignatures)) {
            return std::pair(constructor.first, constructor.second);
        }
        Logger::log("constructor did not match", constructor.first);
    }
    return {};
}

std::string ClassTypeSignature::toDetailString() {
    return "jet.class." + this->getId();
}

std::string ClassTypeSignature::toString() {
    return "CLASS_TYPE_SIGNATURE";
}

TypeSource ClassTypeSignature::getTypeSource() {
    return CLASS_TYPE_SOURCE;
}

bool ClassTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = (ClassInstanceTypeSignature*)otherType;
        return this->isEqualTo(classInstanceTypeSignature->getClassTypeSignature());
    }
    return this->isEqualTo(otherType);
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