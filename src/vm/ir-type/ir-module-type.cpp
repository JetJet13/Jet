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

std::shared_ptr<IRType> IRModuleType::clone() {
    auto keyTypeMapClone = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (auto keyValue : _keyTypeMap) {
        keyTypeMapClone[keyValue.first] = keyValue.second->clone();
    }
    auto clone = std::make_shared<IRModuleType>(_type, _keyIndexMap, _keyIdMap, keyTypeMapClone);
    this->initClone(clone);
    return clone;
}