//
// Created by Johny Georges on 2024-05-15.
//

#include "class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../interface-type-signature/interface-type-signature.h"

ClassInstanceTypeSignature::ClassInstanceTypeSignature() {
    _classTypeSignature = {};
    _constructorInfo = {};
}

ClassInstanceTypeSignature::ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature, std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> constructorInfo) {
    _classTypeSignature = classTypeSignature;
    _constructorInfo = constructorInfo;
}

ClassTypeSignature* ClassInstanceTypeSignature::getClassTypeSignature() {
    return _classTypeSignature.value();
}

TypeSignatureMap<TypeSignature>* ClassInstanceTypeSignature::getClassInterface() {
    return _classTypeSignature.value()->getInterface();
}

ClassConstructorTypeSignature* ClassInstanceTypeSignature::getConstructorTypeSignature() {
    return _constructorInfo.value().second;
}

bool ClassInstanceTypeSignature::hasConstructorInfo() {
    return _constructorInfo.has_value();
}

std::string ClassInstanceTypeSignature::getConstructorId() {
    return _constructorInfo.value().first;
}

void ClassInstanceTypeSignature::setConstructorInfo(std::pair<std::string, ClassConstructorTypeSignature*> constructorInfo) {
    _constructorInfo = constructorInfo;
}

std::string ClassInstanceTypeSignature::toDetailString() {
    return "jet.class_instance." + _classTypeSignature.value()->toDetailString();
}

std::string ClassInstanceTypeSignature::toString() {
    return "CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource ClassInstanceTypeSignature::getTypeSource() {
    return CLASS_INSTANCE_TYPE_SOURCE;
}

bool ClassInstanceTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (otherType->typeSourceIs(CLASS_TYPE_SOURCE)){
        auto classTypeSignature = (ClassTypeSignature*)otherType;
        return this->getClassTypeSignature()->isEqualTo(classTypeSignature);
    } else if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = (ClassInstanceTypeSignature*)otherType;
        return this->getClassTypeSignature()->isEqualTo(classInstanceTypeSignature->getClassTypeSignature());
    } else if (otherType->typeSourceIs(INTERFACE_TYPE_SOURCE)) {
        auto interfaceTypeSignature = (InterfaceTypeSignature*)otherType;
        return interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(this->getClassInterface());
    }
    return this->isEqualTo(otherType);
}

bool ClassInstanceTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

bool ClassInstanceTypeSignature::isInvalid() {
    return !_classTypeSignature.has_value();
}

void ClassInstanceTypeSignature::print() {
    Logger::log(this->toString());
}