//
// Created by Johny Georges on 2024-05-15.
//

#include "class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ClassInstanceTypeSignature::ClassInstanceTypeSignature() {
    _classTypeSignature = {};
    _constructorInfo = {};
}

ClassInstanceTypeSignature::ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature, std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> constructorInfo) {
    _classTypeSignature = classTypeSignature;
    if (constructorInfo) {
        Logger::log("CONSTRUCTOR INFO");
    } else {
        Logger::log("NO CONSTRUCTOR INFO");
    }
    _constructorInfo = constructorInfo;
}

ClassTypeSignature* ClassInstanceTypeSignature::getClassTypeSignature() {
    return _classTypeSignature.value();
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

std::string ClassInstanceTypeSignature::toString() {
    return "CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource ClassInstanceTypeSignature::getTypeSource() {
    return CLASS_INSTANCE_TYPE_SOURCE;
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