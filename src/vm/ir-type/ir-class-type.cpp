//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-type.h"
#include "../../shared/utils/logger/logger.h"

#include <utility>

IRClassType::IRClassType(std::string name, IRStructRefType* classProperties, std::string preConstructorName): IRType(classProperties->getType()) {
    _name = name;
    _classProperties = classProperties;
    _classScopeType = std::optional<IRParameterType*>();
    _classConstructors = std::unordered_map<std::string, IRFunctionType*>();
    _classMethods = std::unordered_map<std::string, IRFunctionType*>();
    _classStaticMethods = std::unordered_map<std::string, IRFunctionType*>();
    _preConstructorName = std::move(preConstructorName);
}

IRClassType::IRClassType(std::string name, IRStructRefType* classProperties, std::optional<IRParameterType*> classScopeType, std::unordered_map<std::string, IRFunctionType*> classConstructors, std::unordered_map<std::string, IRFunctionType*> classMethods, std::unordered_map<std::string, IRFunctionType*> classStaticMethods, std::unordered_map<std::string, IRType*> classStaticProperties, std::string preConstructorName) : IRType(classProperties->getType()) {
    _name = name;
    _classProperties = classProperties;
    _classScopeType = classScopeType;
    _classConstructors = std::move(classConstructors);
    _classMethods = std::move(classMethods);
    _classStaticMethods = std::move(classStaticMethods);
    _classStaticProperties = std::move(classStaticProperties);
    _preConstructorName = std::move(preConstructorName);
}

std::optional<IRParameterType*> IRClassType::getClassScopeParameterType() {
    return _classScopeType;
}

std::optional<IRFunctionType*> IRClassType::getIRTypeForConstructor(std::string constructorId) {
    auto result = _classConstructors.find(constructorId);
    if (result == _classConstructors.end()) {
        return {};
    }
    return result->second;
}

std::optional<IRFunctionType*> IRClassType::getIRTypeForMethod(std::string methodName) {
    auto result = _classMethods.find(methodName);
    if (result == _classMethods.end()) {
        return {};
    }
    return result->second;
}

std::optional<IRType*> IRClassType::getIRTypeForStaticProperty(std::string propertyName) {
    auto result = _classStaticProperties.find(propertyName);
    if (result == _classStaticProperties.end()) {
        return {};
    }
    return result->second;
}

std::optional<IRFunctionType*> IRClassType::getIRTypeForStaticMethod(std::string methodName) {
    auto result = _classStaticMethods.find(methodName);
    if (result == _classStaticMethods.end()) {
        return {};
    }
    return result->second;
}

std::string IRClassType::getIRMethodName(std::string methodName) {
    return this->getName() + "." + methodName;
}

std::string IRClassType::getIRPropertyName(std::string propertyName) {
    return this->getName() + "." + propertyName;
}


llvm::Type* IRClassType::getValueType() {
    return this->getType()->getStructElementType(0);
}

IRStructRefType* IRClassType::getClassProperties() {
    return _classProperties;
}

std::string IRClassType::getPreConstructorName() {
    return _preConstructorName;
}

std::string IRClassType::getName() {
    return _name;
}


void IRClassType::setProperties(IRStructRefType* classProperties) {
    _classProperties = classProperties;
}

void IRClassType::setClassScopeType(std::optional<IRParameterType*> classScopeType) {
    _classScopeType = classScopeType;
}

void IRClassType::addStaticProperty(std::string staticPropertyName, IRType* irType) {
    _classStaticProperties[staticPropertyName] = irType;
}

void IRClassType::addMethod(std::string methodName, IRFunctionType* irType) {
    _classMethods[methodName] = irType;
}

void IRClassType::addStaticMethod(std::string methodName, IRFunctionType* irType) {
    _classStaticMethods[methodName] = irType;
}

void IRClassType::addConstructor(std::string constructorName, IRFunctionType* irType) {
    _classConstructors[constructorName] = irType;
}

std::string IRClassType::stripClassNameFromKey(std::string key) {
    key.erase(0, this->getName().size() + 1);
    return key;
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

IRClassType* IRClassType::clone() {
    auto classPropertiesClone = _classProperties->clone();
    auto clone = new IRClassType(_name, classPropertiesClone, _classScopeType, _classConstructors, _classMethods, _classStaticMethods, _classStaticProperties, _preConstructorName);
    this->initClone(clone);
    return clone;
}

void IRClassType::print() {
    Logger::log("IR CLASS TYPE");
    _type->print(llvm::outs());
}