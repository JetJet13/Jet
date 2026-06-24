//
// Created by Johny Georges on 2024-12-31.
//

#include "ir-new-class-instance-type.h"
#include "../../shared/utils/logger/logger.h"

IRNewClassInstanceType::IRNewClassInstanceType(IRClassType* irClassType, std::string constructorId, IRStructRefType* irClassInstancePropertiesType) : IRType(irClassInstancePropertiesType->getType()) {
    _id = irClassType->getId();
    _irClassInstancePropertiesType = irClassInstancePropertiesType;
    _irClassType = irClassType;
    _constructorId = constructorId;
    _value = irClassInstancePropertiesType->getValue();
}

IRStructRefType* IRNewClassInstanceType::getIRClassPropertiesType() {
    return _irClassInstancePropertiesType;
}

IRClassType* IRNewClassInstanceType::getIRClassType() {
    return _irClassType;
}

IRFunctionType* IRNewClassInstanceType::getIRConstructorType() {
    return _irClassType->getIRTypeForConstructor(_constructorId).value();
}

std::string IRNewClassInstanceType::getIRMethodName(std::string methodName) {
    return _irClassType->getName() + "." + methodName;
}

std::string IRNewClassInstanceType::getIRPropertyName(std::string propertyName) {
    return _irClassType->getName() + "." + propertyName;
}

unsigned long IRNewClassInstanceType::getIndexForProperty(std::string propertyName) {
    return _irClassInstancePropertiesType->getStructIRType()->getIndexForKey(this->getIRPropertyName(propertyName));
}

IRType* IRNewClassInstanceType::getIRTypeForProperty(std::string propertyName) {
    return _irClassInstancePropertiesType->getStructIRType()->getIRTypeForKey(this->getIRPropertyName(propertyName));
}

std::optional<IRFunctionType*> IRNewClassInstanceType::getIRTypeForMethod(std::string methodName) {
    return _irClassType->getIRTypeForMethod(this->getIRMethodName(methodName));
}

uint64_t IRNewClassInstanceType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return _irClassInstancePropertiesType->getSizeInBytes();
}

llvm::StructType* IRNewClassInstanceType::getType() {
    return _irClassInstancePropertiesType->getType();
}

bool IRNewClassInstanceType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRNewClassInstanceType::isNewClassInstanceType() {
    return true;
}

llvm::Align IRNewClassInstanceType::getAlignment() {
    return _irClassType->getAlignment();
}

IRNewClassInstanceType* IRNewClassInstanceType::clone() {
    auto classPropertiesClone = _irClassInstancePropertiesType->clone();
    auto clone = new IRNewClassInstanceType(_irClassType, _constructorId, classPropertiesClone);
    this->initClone(clone);
    return clone;
}

void IRNewClassInstanceType::print() {
    Logger::log("IR NEW CLASS INSTANCE TYPE");
    _type->print(llvm::outs());
}