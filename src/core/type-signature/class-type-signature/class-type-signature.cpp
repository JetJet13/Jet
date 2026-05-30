//
// Created by Johny Georges on 2024-04-30.
//

#include <utility>
#include "class-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../struct-type-signature/struct-type-signature.h"
#include "class-instance-type-signature/class-instance-type-signature.h"

ClassTypeSignature::ClassTypeSignature() {
    _constructors = TypeSignatureMap<ClassConstructorTypeSignature>();
    _staticProperties = TypeSignatureMap<ClassPropertyTypeSignature>();
    _instanceProperties = TypeSignatureMap<ClassPropertyTypeSignature>();
    _staticMethods = TypeSignatureMap<ClassMethodTypeSignature>();
    _instanceMethods = TypeSignatureMap<ClassMethodTypeSignature>();
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

TypeSignatureMap<ClassPropertyTypeSignature>* ClassTypeSignature::getStaticProperties() {
    return &_staticProperties;
}

TypeSignatureMap<ClassPropertyTypeSignature>* ClassTypeSignature::getInstanceProperties() {
    return &_instanceProperties;
}

TypeSignatureMap<ClassMethodTypeSignature>* ClassTypeSignature::getStaticMethods() {
    return &_staticMethods;
}

TypeSignatureMap<ClassMethodTypeSignature>* ClassTypeSignature::getInstanceMethods() {
    return &_instanceMethods;
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
    if (classPropertyTypeSignature->isStatic()) {
        _staticProperties.insert(key, classPropertyTypeSignature);
    } else {
        _instanceProperties.insert(key, classPropertyTypeSignature);
    }
    if (classPropertyTypeSignature->getAccessModifier()->isPublic()) {
        auto interfaceKey = this->stripClassNameFromKey(key);
        _interface.insert(interfaceKey, classPropertyTypeSignature->convertToVariableTypeSignature());
    }
    return this;
}

ClassTypeSignature* ClassTypeSignature::addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature) {
    if (classMethodTypeSignature->isStatic()) {
        _staticMethods.insert(key, classMethodTypeSignature);
    } else {
        _instanceMethods.insert(key, classMethodTypeSignature);
    }
    if (classMethodTypeSignature->getAccessModifier()->isPublic()) {
        auto interfaceKey = this->stripClassNameFromKey(key);
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
    }
    return {};
}

std::string ClassTypeSignature::stripClassNameFromKey(std::string key) {
    key.erase(0, this->getId().size() + 1);
    return key;
}

std::string ClassTypeSignature::addClassNameToKey(std::string key) {
    return this->getId() + "." + key;
}

TypeSignature* ClassTypeSignature::convertToVariableTypeSignature() {
    auto classInstance = new ClassInstanceTypeSignature(this);
    classInstance->setModuleId(this->getModuleId());
    classInstance->setId(this->getId());
    classInstance->setKeyId(this->getKeyId());
    return classInstance;
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
    if (this->getId() == otherType->getId()) return true;
    if (otherType->typeSourceIs(NEW_CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = (NewClassInstanceTypeSignature*)otherType;
        return this->isEqualTo(classInstanceTypeSignature->getClassTypeSignature());
    }
    return this->isEqualTo(otherType);
}

bool ClassTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getId() == otherType->getId()) return true;
    if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto classInstance = (ClassInstanceTypeSignature*)otherType;
        return this->getInterface()->isEqualTo(classInstance->getKeyValuePairs());
    }
    return this->getTypeSource() == otherType->getTypeSource();
}

void ClassTypeSignature::copyFrom(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = (ClassTypeSignature*)otherType;
    _instanceProperties = *other->getInstanceProperties();
    _staticProperties = *other->getStaticProperties();
    _constructors = *other->getConstructors();
    _instanceMethods = *other->getInstanceMethods();
    _staticMethods = *other->getStaticMethods();
}

void ClassTypeSignature::print() {
    Logger::log(this->toString());
}