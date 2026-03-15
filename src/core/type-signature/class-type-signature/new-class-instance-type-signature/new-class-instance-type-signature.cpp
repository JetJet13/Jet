//
// Created by Johny Georges on 2024-05-15.
//

#include "new-class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../interface-type-signature/interface-type-signature.h"
#include "../class-instance-type-signature/class-instance-type-signature.h"

NewClassInstanceTypeSignature::NewClassInstanceTypeSignature() {
    _classTypeSignature = {};
    _constructorInfo = {};
}

NewClassInstanceTypeSignature::NewClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature, std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> constructorInfo) {
    _classTypeSignature = classTypeSignature;
    _constructorInfo = constructorInfo;
}

ClassTypeSignature* NewClassInstanceTypeSignature::getClassTypeSignature() {
    return _classTypeSignature.value();
}

TypeSignatureMap<TypeSignature>* NewClassInstanceTypeSignature::getClassInterface() {
    return _classTypeSignature.value()->getInterface();
}

ClassConstructorTypeSignature* NewClassInstanceTypeSignature::getConstructorTypeSignature() {
    return _constructorInfo.value().second;
}

std::optional<ClassMethodTypeSignature*> NewClassInstanceTypeSignature::findMethod(std::string methodName) {
    auto methodId = _classTypeSignature.value()->getId() + "." + methodName;
    return _classTypeSignature.value()->getMethods()->find(methodId);
}

std::optional<ClassPropertyTypeSignature*> NewClassInstanceTypeSignature::findProperty(std::string propertyName) {
    auto propertyId = _classTypeSignature.value()->getId() + "." + propertyName;
    return _classTypeSignature.value()->getInstanceProperties()->find(propertyId);
}

bool NewClassInstanceTypeSignature::hasConstructorInfo() {
    return _constructorInfo.has_value();
}

std::string NewClassInstanceTypeSignature::getConstructorId() {
    return _constructorInfo.value().first;
}

void NewClassInstanceTypeSignature::setConstructorInfo(std::pair<std::string, ClassConstructorTypeSignature*> constructorInfo) {
    _constructorInfo = constructorInfo;
}

TypeSignature* NewClassInstanceTypeSignature::convertToVariableTypeSignature() {
    auto classTypeSignature = _classTypeSignature.value();
    auto classInstance = new ClassInstanceTypeSignature(classTypeSignature);
    classInstance->setId(classTypeSignature->getId());
    classInstance->setKeyId(classTypeSignature->getKeyId());
    return classInstance;
}

std::string NewClassInstanceTypeSignature::toDetailString() {
    return "jet.new_class_instance." + _classTypeSignature.value()->toDetailString();
}

std::string NewClassInstanceTypeSignature::toString() {
    return "NEW_CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource NewClassInstanceTypeSignature::getTypeSource() {
    return NEW_CLASS_INSTANCE_TYPE_SOURCE;
}

bool NewClassInstanceTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (otherType->typeSourceIs(CLASS_TYPE_SOURCE)){
        auto classTypeSignature = (ClassTypeSignature*)otherType;
        return this->getClassTypeSignature()->isEqualTo(classTypeSignature);
    } else if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = (ClassInstanceTypeSignature*)otherType;
        return this->getClassTypeSignature()->isEqualTo(classInstanceTypeSignature);
    } else if (otherType->typeSourceIs(NEW_CLASS_INSTANCE_TYPE_SOURCE)){
        auto newClassInstanceTypeSignature = (NewClassInstanceTypeSignature*)otherType;
        return this->getClassTypeSignature()->isEqualTo(newClassInstanceTypeSignature->getClassTypeSignature());
    } else if (otherType->typeSourceIs(INTERFACE_TYPE_SOURCE)) {
        auto interfaceTypeSignature = (InterfaceTypeSignature*)otherType;
        return interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(this->getClassInterface());
    }
    return this->isEqualTo(otherType);
}

bool NewClassInstanceTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

bool NewClassInstanceTypeSignature::isInvalid() {
    return !_classTypeSignature.has_value();
}

void NewClassInstanceTypeSignature::print() {
    Logger::log(this->toString());
}