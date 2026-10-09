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
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-type.h"
#include "../../shared/utils/logger/logger.h"

#include <utility>

IRClassType::IRClassType(std::string name, std::shared_ptr<IRStructRefType> classProperties, std::string preConstructorName): IRType(classProperties->getType()) {
    _name = name;
    _classProperties = classProperties;
    _classScopeType = std::optional<std::shared_ptr<IRParameterType>>();
    _classConstructors = std::unordered_map<std::string, std::shared_ptr<IRFunctionType>>();
    _classMethods = std::unordered_map<std::string, std::shared_ptr<IRFunctionType>>();
    _classStaticMethods = std::unordered_map<std::string, std::shared_ptr<IRFunctionType>>();
    _preConstructorName = std::move(preConstructorName);
}

IRClassType::IRClassType(std::string name, std::shared_ptr<IRStructRefType> classProperties, std::optional<std::shared_ptr<IRParameterType>> classScopeType, std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> classConstructors, std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> classMethods, std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> classStaticMethods, std::unordered_map<std::string, std::shared_ptr<IRType>> classStaticProperties, std::string preConstructorName) : IRType(classProperties->getType()) {
    _name = name;
    _classProperties = classProperties;
    _classScopeType = classScopeType;
    _classConstructors = std::move(classConstructors);
    _classMethods = std::move(classMethods);
    _classStaticMethods = std::move(classStaticMethods);
    _classStaticProperties = std::move(classStaticProperties);
    _preConstructorName = std::move(preConstructorName);
}

std::optional<std::shared_ptr<IRParameterType>> IRClassType::getClassScopeParameterType() {
    return _classScopeType;
}

std::optional<std::shared_ptr<IRFunctionType>> IRClassType::getIRTypeForConstructor(std::string constructorId) {
    auto result = _classConstructors.find(constructorId);
    if (result == _classConstructors.end()) {
        return {};
    }
    return result->second;
}

std::optional<std::shared_ptr<IRFunctionType>> IRClassType::getIRTypeForMethod(std::string methodName) {
    auto result = _classMethods.find(methodName);
    if (result == _classMethods.end()) {
        return {};
    }
    return result->second;
}

std::optional<std::shared_ptr<IRType>> IRClassType::getIRTypeForStaticProperty(std::string propertyName) {
    auto result = _classStaticProperties.find(propertyName);
    if (result == _classStaticProperties.end()) {
        return {};
    }
    return result->second;
}

std::optional<std::shared_ptr<IRFunctionType>> IRClassType::getIRTypeForStaticMethod(std::string methodName) {
    auto result = _classStaticMethods.find(methodName);
    if (result == _classStaticMethods.end()) {
        return {};
    }
    return result->second;
}

std::string IRClassType::getIRMethodName(std::string methodName) {
    return this->getName() + "." + methodName;
}

std::string IRClassType::getIRStaticMethodName(std::string methodName) {
    return this->addStaticSuffix(this->getIRMethodName(methodName));
}

std::string IRClassType::addStaticSuffix(std::string name) {
    return name + ".static";
}

std::string IRClassType::getIRPropertyName(std::string propertyName) {
    return this->getName() + "." + propertyName;
}

std::string IRClassType::getIRStaticPropertyName(std::string propertyName) {
    return this->addStaticSuffix(this->getIRPropertyName(propertyName));
}

llvm::Type* IRClassType::getValueType() {
    return this->getType()->getStructElementType(0);
}

std::shared_ptr<IRStructRefType> IRClassType::getClassProperties() {
    return _classProperties;
}

std::string IRClassType::getPreConstructorName() {
    return _preConstructorName;
}

std::string IRClassType::getName() {
    return _name;
}


void IRClassType::setProperties(std::shared_ptr<IRStructRefType> classProperties) {
    _classProperties = classProperties;
}

void IRClassType::setClassScopeType(std::optional<std::shared_ptr<IRParameterType>> classScopeType) {
    _classScopeType = classScopeType;
}

void IRClassType::addStaticProperty(std::string staticPropertyName, std::shared_ptr<IRType> irType) {
    _classStaticProperties[staticPropertyName] = irType;
}

void IRClassType::addMethod(std::string methodName, std::shared_ptr<IRFunctionType> irType) {
    _classMethods[methodName] = irType;
}

void IRClassType::addStaticMethod(std::string methodName, std::shared_ptr<IRFunctionType> irType) {
    _classStaticMethods[methodName] = irType;
}

void IRClassType::addConstructor(std::string constructorName, std::shared_ptr<IRFunctionType> irType) {
    _classConstructors[constructorName] = irType;
}

llvm::Type* IRClassType::getType() {
    return _classProperties->getType();
}

bool IRClassType::isClassType() {
    return true;
}

bool IRClassType::containsTypeThatRequiresFreeing() {
    return _classProperties->containsTypeThatRequiresFreeing();
}

llvm::Align IRClassType::getAlignment() {
    return _classProperties->getAlignment();
}

std::shared_ptr<IRType> IRClassType::clone() {
    auto classPropertiesClone = std::dynamic_pointer_cast<IRStructRefType>(_classProperties->clone());
    auto clone = std::make_shared<IRClassType>(_name, classPropertiesClone, _classScopeType, _classConstructors, _classMethods, _classStaticMethods, _classStaticProperties, _preConstructorName);
    this->initClone(clone);
    return clone;
}

void IRClassType::print() {
    Logger::log("IR CLASS TYPE");
    _type->print(llvm::outs());
}