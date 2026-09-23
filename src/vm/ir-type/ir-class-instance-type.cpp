//
// Created by Johny Georges on 2025-12-27.
//

#include "ir-class-instance-type.h"
#include "../../shared/utils/logger/logger.h"

IRClassInstanceType::IRClassInstanceType(std::shared_ptr<IRClassType> irClassType) : IRType(irClassType->getClassProperties()->getType()) {
    _id = irClassType->getId();
    _irClassType = irClassType;
}

std::shared_ptr<IRStructRefType> IRClassInstanceType::getIRClassPropertiesType() {
    return _irClassType->getClassProperties();
}

std::shared_ptr<IRClassType> IRClassInstanceType::getIRClassType() {
    return _irClassType;
}

std::string IRClassInstanceType::getIRMethodName(std::string methodName) {
    return _irClassType->getIRMethodName(std::move(methodName));
}

std::string IRClassInstanceType::getIRPropertyName(std::string propertyName) {
    return _irClassType->getIRPropertyName(std::move(propertyName));
}

uint64_t IRClassInstanceType::getIndexForProperty(std::string propertyName) {
    return this->getIRClassPropertiesType()->getStructIRType()->getIndexForKey(this->getIRPropertyName(propertyName));
}

std::shared_ptr<IRType> IRClassInstanceType::getIRTypeForProperty(std::string propertyName) {
    return this->getIRClassPropertiesType()->getStructIRType()->getIRTypeForKey(this->getIRPropertyName(propertyName));
}

std::optional<std::shared_ptr<IRFunctionType>> IRClassInstanceType::getIRTypeForMethod(std::string methodName) {
    return _irClassType->getIRTypeForMethod(this->getIRMethodName(methodName));
}

bool IRClassInstanceType::requiresArc() {
    return false;
}

uint64_t IRClassInstanceType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return this->getIRClassPropertiesType()->getSizeInBytes();
}

llvm::StructType* IRClassInstanceType::getType() {
    return this->getIRClassPropertiesType()->getType();
}

bool IRClassInstanceType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRClassInstanceType::isClassInstanceType() {
    return true;
}

llvm::Align IRClassInstanceType::getAlignment() {
    return this->getIRClassPropertiesType()->getAlignment();
}

std::shared_ptr<IRType> IRClassInstanceType::clone() {
    auto clone = std::make_shared<IRClassInstanceType>(_irClassType);
    this->initClone(clone);
    return clone;
}

void IRClassInstanceType::print() {
    Logger::log("IR CLASS INSTANCE TYPE");
    _type->print(llvm::outs());
}