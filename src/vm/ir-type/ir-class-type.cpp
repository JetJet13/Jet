//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-type.h"

#include <utility>

IRClassType::IRClassType(IRStructType* classProperties, std::optional<IRParameterType*> classScopeType, std::unordered_map<std::string, IRFunctionType*> classConstructors, std::unordered_map<std::string, IRFunctionType*> classMethods) : IRType(*this) {
    _classProperties = classProperties;
    _classScopeType = classScopeType;
    _classConstructors = std::move(classConstructors);
    _classMethods = std::move(classMethods);
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

bool IRClassType::isClassType() {
    return true;
}