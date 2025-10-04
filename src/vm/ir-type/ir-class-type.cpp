//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-type.h"
#include "../../shared/utils/logger/logger.h"

#include <utility>

IRClassType::IRClassType(std::string name, IRStructType* classProperties, std::optional<IRParameterType*> classScopeType, std::unordered_map<std::string, IRFunctionType*> classConstructors, std::unordered_map<std::string, IRFunctionType*> classMethods, std::string preConstructorName) : IRType(classProperties->getType()) {
    _name = name;
    _classProperties = classProperties;
    _classScopeType = classScopeType;
    _classConstructors = std::move(classConstructors);
    _classMethods = std::move(classMethods);
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

llvm::Type* IRClassType::getValueType() {
    return this->getType()->getStructElementType(0);
}

IRStructType* IRClassType::getClassProperties() {
    return _classProperties;
}

std::string IRClassType::getPreConstructorName() {
    return _preConstructorName;
}

std::string IRClassType::getName() {
    return _name;
}

bool IRClassType::isClassType() {
    return true;
}

bool IRClassType::containsTypeThatRequiresFreeing() {
    return _classProperties->containsTypeThatRequiresFreeing();
}

void IRClassType::print() {
    Logger::log("IR CLASS TYPE");
    _type->print(llvm::outs());
}