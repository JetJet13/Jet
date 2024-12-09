//
// Created by Johny Georges on 2024-12-05.
//

#include "ir-class-type.h"

#include <utility>

IRClassType::IRClassType(IRStructType* classProperties, IRParameterType* classScopeType, std::unordered_map<std::string, IRFunctionType*> classConstructors, std::unordered_map<std::string, IRFunctionType*> classMethods) : IRType(*this) {
    _classProperties = classProperties;
    _classScopeType = classScopeType;
    _classConstructors = std::move(classConstructors);
    _classMethods = std::move(classMethods);
}

llvm::Type* IRClassType::getValueType() {
    return this->getType()->getStructElementType(0);
}

bool IRClassType::isClassType() {
    return true;
}