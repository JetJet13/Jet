//
// Created by Johny Georges on 2024-10-29.
//

#include "ir-module-type.h"

llvm::Type* IRModuleType::getValueType() {
    return this->getType()->getStructElementType(0);
}

bool IRModuleType::isModuleType() {
    return true;
}

IRModuleType* IRModuleType::clone() {
    auto keyTypeMapClone = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : _keyTypeMap) {
        keyTypeMapClone[keyValue.first] = keyValue.second->clone();
    }
    auto clone = new IRModuleType(_type, _keyIndexMap, keyTypeMapClone);
    this->initClone(clone);
    return clone;
}