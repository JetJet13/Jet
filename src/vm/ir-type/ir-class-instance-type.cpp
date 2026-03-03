//
// Created by Johny Georges on 2025-12-27.
//

#include "ir-class-instance-type.h"
#include "../../shared/utils/logger/logger.h"

IRClassInstanceType::IRClassInstanceType(IRClassType* irClassType, IRStructRefType* irClassInstancePropertiesType) : IRType(irClassInstancePropertiesType->getType()) {
    _id = irClassType->getId();
    _irClassInstancePropertiesType = irClassInstancePropertiesType;
    _irClassType = irClassType;
}

IRStructRefType* IRClassInstanceType::getIRClassPropertiesType() {
    return _irClassInstancePropertiesType;
}

IRClassType* IRClassInstanceType::getIRClassType() {
    return _irClassType;
}

std::string IRClassInstanceType::getIRMethodName(std::string methodName) {
    return _irClassType->getName() + "." + methodName;
}

std::string IRClassInstanceType::getIRPropertyName(std::string propertyName) {
    return _irClassType->getName() + "." + propertyName;
}

unsigned long IRClassInstanceType::getIndexForProperty(std::string propertyName) {
    return _irClassInstancePropertiesType->getStructIRType()->getIndexForKey(this->getIRPropertyName(propertyName));
}

IRType* IRClassInstanceType::getIRTypeForProperty(std::string propertyName) {
    return _irClassInstancePropertiesType->getStructIRType()->getIRTypeForKey(this->getIRPropertyName(propertyName));
}

std::optional<IRFunctionType*> IRClassInstanceType::getIRTypeForMethod(std::string methodName) {
    return _irClassType->getIRTypeForMethod(this->getIRMethodName(methodName));
}

bool IRClassInstanceType::requiresArc() {
    return false;
}

IRTypeValueInstructionNode* IRClassInstanceType::getValue() {
    return _irClassInstancePropertiesType->getValue();
}

uint64_t IRClassInstanceType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return _irClassInstancePropertiesType->getSizeInBytes();
}

llvm::StructType* IRClassInstanceType::getType() {
    return _irClassInstancePropertiesType->getType();
}

bool IRClassInstanceType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRClassInstanceType::isClassInstanceType() {
    return true;
}

llvm::Align IRClassInstanceType::getAlignment() {
    return _irClassInstancePropertiesType->getAlignment();
}

IRClassInstanceType* IRClassInstanceType::clone() {
    auto classPropertiesClone = _irClassInstancePropertiesType->clone();
    auto clone = new IRClassInstanceType(_irClassType, classPropertiesClone);
    this->initClone(clone);
    return clone;
}

void IRClassInstanceType::print() {
    Logger::log("IR CLASS INSTANCE TYPE");
    _type->print(llvm::outs());
}