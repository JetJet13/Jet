// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-12-31.
//

#include "ir-new-class-instance-type.h"
#include "../../shared/utils/logger/logger.h"

IRNewClassInstanceType::IRNewClassInstanceType(std::shared_ptr<IRClassType> irClassType, std::string constructorId, std::shared_ptr<IRStructRefType> irClassInstancePropertiesType) : IRType(irClassInstancePropertiesType->getType()) {
    _id = irClassType->getId();
    _irClassInstancePropertiesType = irClassInstancePropertiesType;
    _irClassType = irClassType;
    _constructorId = constructorId;
    _value = irClassInstancePropertiesType->getValue();
}

std::shared_ptr<IRStructRefType> IRNewClassInstanceType::getIRClassPropertiesType() {
    return _irClassInstancePropertiesType;
}

std::shared_ptr<IRClassType> IRNewClassInstanceType::getIRClassType() {
    return _irClassType;
}

std::shared_ptr<IRFunctionType> IRNewClassInstanceType::getIRConstructorType() {
    return _irClassType->getIRTypeForConstructor(_constructorId).value();
}

std::string IRNewClassInstanceType::getIRMethodName(std::string methodName) {
    return _irClassType->getName() + "." + methodName;
}

std::string IRNewClassInstanceType::getIRPropertyName(std::string propertyName) {
    return _irClassType->getName() + "." + propertyName;
}

uint64_t IRNewClassInstanceType::getIndexForProperty(std::string propertyName) {
    return _irClassInstancePropertiesType->getStructIRType()->getIndexForKey(this->getIRPropertyName(propertyName));
}

std::shared_ptr<IRType> IRNewClassInstanceType::getIRTypeForProperty(std::string propertyName) {
    return _irClassInstancePropertiesType->getStructIRType()->getIRTypeForKey(this->getIRPropertyName(propertyName));
}

std::optional<std::shared_ptr<IRFunctionType>> IRNewClassInstanceType::getIRTypeForMethod(std::string methodName) {
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

std::shared_ptr<IRType> IRNewClassInstanceType::clone() {
    auto classPropertiesClone = std::dynamic_pointer_cast<IRStructRefType>(_irClassInstancePropertiesType->clone());
    auto clone = std::make_shared<IRNewClassInstanceType>(_irClassType, _constructorId, classPropertiesClone);
    this->initClone(clone);
    return clone;
}

void IRNewClassInstanceType::print() {
    Logger::log("IR NEW CLASS INSTANCE TYPE");
    _type->print(llvm::outs());
}