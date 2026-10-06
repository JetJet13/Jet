//
// Created by Johny Georges on 2024-04-30.
//

#include <utility>
#include "class-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../struct-type-signature/struct-type-signature.h"
#include "class-instance-type-signature/class-instance-type-signature.h"
#include "../../../shared/utils/function-id-generator/function-id-generator.h"

ClassTypeSignature::ClassTypeSignature() {
    _constructors = TypeSignatureMap<std::shared_ptr<ClassConstructorTypeSignature>>();
    _staticProperties = TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>();
    _instanceProperties = TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>();
    _staticMethods = TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>();
    _staticMethodLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>>();
    _instanceMethods = TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>();
    _instanceMethodLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>>();
    _implements = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
    _interface = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
    _classScopeParameter = ParameterListItemTypeSignature::createClassScopeParameter();
}

std::shared_ptr<ParameterListItemTypeSignature> ClassTypeSignature::getClassScopeParameter() {
    return _classScopeParameter;
}

TypeSignatureMap<std::shared_ptr<ClassConstructorTypeSignature>>* ClassTypeSignature::getConstructors() {
    return &_constructors;
}

TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>* ClassTypeSignature::getStaticProperties() {
    return &_staticProperties;
}

TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>* ClassTypeSignature::getInstanceProperties() {
    return &_instanceProperties;
}

TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>* ClassTypeSignature::getStaticMethods() {
    return &_staticMethods;
}

TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>* ClassTypeSignature::getInstanceMethods() {
    return &_instanceMethods;
}

std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> ClassTypeSignature::findInstanceMethodsByName(std::string name) {
    auto instanceMethodMap = _instanceMethodLookupTable->find(name);
    if (instanceMethodMap == _instanceMethodLookupTable->end()) {
        return {};
    }
    return instanceMethodMap->second;
}

std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> ClassTypeSignature::findStaticMethodsByName(std::string name) {
    auto staticMethodMap = _staticMethodLookupTable->find(name);
    if (staticMethodMap == _staticMethodLookupTable->end()) {
        return {};
    }
    return staticMethodMap->second;
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* ClassTypeSignature::getImplements() {
    return &_implements;
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* ClassTypeSignature::getInterface() {
    return &_interface;
}

std::shared_ptr<ClassTypeSignature> ClassTypeSignature::addConstructor(std::string key, std::shared_ptr<ClassConstructorTypeSignature> classConstructorTypeSignature) {
    _constructors.insert(key, classConstructorTypeSignature);
    return std::dynamic_pointer_cast<ClassTypeSignature>(shared_from_this());
}

std::shared_ptr<ClassTypeSignature> ClassTypeSignature::addProperty(std::string key, std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature) {
    if (classPropertyTypeSignature->isStatic()) {
        _staticProperties.insert(key, classPropertyTypeSignature);
    } else {
        _instanceProperties.insert(key, classPropertyTypeSignature);
    }
    if (classPropertyTypeSignature->getAccessModifier()->isPublic()) {
        auto interfaceKey = this->stripClassNameFromKey(key);
        _interface.insert(interfaceKey, classPropertyTypeSignature->convertToVariableTypeSignature());
    }
    return std::dynamic_pointer_cast<ClassTypeSignature>(shared_from_this());
}

std::shared_ptr<ClassTypeSignature> ClassTypeSignature::addMethod(std::string key, std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature) {
    auto methodName = FunctionIdGenerator::getNameFromId(this->stripClassNameFromKey(key));

    if (classMethodTypeSignature->isStatic()) {
        _staticMethods.insert(key, classMethodTypeSignature);
        auto existing = _staticMethodLookupTable->find(methodName);
        if (existing == _staticMethodLookupTable->end()) {
            auto staticMethodLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>();
            staticMethodLookupTable->insert_or_assign(key, classMethodTypeSignature);
            _staticMethodLookupTable->insert_or_assign(methodName, staticMethodLookupTable);
        } else {
            existing->second->insert_or_assign(key, classMethodTypeSignature);
        }
    } else {
        _instanceMethods.insert(key, classMethodTypeSignature);
        auto existing = _instanceMethodLookupTable->find(methodName);
        if (existing == _instanceMethodLookupTable->end()) {
            auto instanceMethodLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>();
            instanceMethodLookupTable->insert_or_assign(key, classMethodTypeSignature);
            _instanceMethodLookupTable->insert_or_assign(methodName, instanceMethodLookupTable);
        } else {
            existing->second->insert_or_assign(key, classMethodTypeSignature);
        }
    }

    if (classMethodTypeSignature->getAccessModifier()->isPublic()) {
        auto interfaceKey = this->stripClassNameFromKey(key);
        _interface.insert(interfaceKey, classMethodTypeSignature->convertToVariableTypeSignature());
    }

    return std::dynamic_pointer_cast<ClassTypeSignature>(shared_from_this());
}

std::shared_ptr<ClassTypeSignature> ClassTypeSignature::addImplementsInterface(std::string key, std::shared_ptr<TypeSignature> interfaceTypeSignature) {
    _implements.insert(key, interfaceTypeSignature);
    return std::dynamic_pointer_cast<ClassTypeSignature>(shared_from_this());
}

void ClassTypeSignature::setClassScopeParameter(std::shared_ptr<ParameterListItemTypeSignature> classScopeParameter) {
    _classScopeParameter = classScopeParameter;
}

bool ClassTypeSignature::isClassScopeParameterNecessary() {
    auto classScopeTypeSignature = std::dynamic_pointer_cast<PointerTypeSignature>(_classScopeParameter->getTypeSignature());
    auto classScopeUnderlyingTypeSignature = std::dynamic_pointer_cast<StructTypeSignature>(classScopeTypeSignature->getUnderlyingType());
    return !classScopeUnderlyingTypeSignature->isEmpty();
}

bool ClassTypeSignature::satisfiesImplementInterfaces() {
    for (auto interface : _implements.getValues()) {
        if (interface->typeSourceIs(INTERFACE_TYPE_SOURCE)) {
            auto interfaceTypeSignature = std::dynamic_pointer_cast<InterfaceTypeSignature>(interface);
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

std::optional<std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>>> ClassTypeSignature::findConstructorForArguments(std::vector<std::shared_ptr<TypeSignature>>* argumentTypeSignatures) {
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

std::shared_ptr<TypeSignature> ClassTypeSignature::convertToVariableTypeSignature() {
    auto classInstance = std::make_shared<ClassInstanceTypeSignature>(std::dynamic_pointer_cast<ClassTypeSignature>(shared_from_this()));
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

bool ClassTypeSignature::hasCircularReferenceWith(std::shared_ptr<ClassTypeSignature> other) {
    if (this->isEqualTo(other)) return false;

    auto otherClassReferenceThisClass = false;
    for (auto otherPropertyTypeSignature : other->getInstanceProperties()->getValues()) {
        if (otherPropertyTypeSignature->getType()->isEquivalentTo(std::dynamic_pointer_cast<ClassTypeSignature>(shared_from_this()))) {
            otherClassReferenceThisClass = true;
            break;
        }
    }

    auto thisClassReferenceOtherClass = false;
    for (auto thisPropertyTypeSignature : _instanceProperties.getValues()) {
        if (thisPropertyTypeSignature->getType()->isEquivalentTo(other)) {
            thisClassReferenceOtherClass = true;
            break;
        }
    }
    return otherClassReferenceThisClass && thisClassReferenceOtherClass;
}

bool ClassTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getId() == otherType->getId()) return true;
    if (otherType->typeSourceIs(NEW_CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = std::dynamic_pointer_cast<NewClassInstanceTypeSignature>(otherType);
        return this->isEqualTo(classInstanceTypeSignature->getClassTypeSignature());
    }
    return this->isEqualTo(otherType);
}

bool ClassTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(otherType);
        return this->getId() == classInstanceTypeSignature->getClass()->getId();
    }
    return this->getId() == otherType->getId();
}

void ClassTypeSignature::copyFrom(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = std::dynamic_pointer_cast<ClassTypeSignature>(otherType);
    _instanceProperties = *other->getInstanceProperties();
    _staticProperties = *other->getStaticProperties();
    _constructors = *other->getConstructors();
    _instanceMethods = *other->getInstanceMethods();
    _staticMethods = *other->getStaticMethods();
}

void ClassTypeSignature::print() {
    Logger::log(this->toString());
}