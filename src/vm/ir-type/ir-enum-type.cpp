//
// Created by Johny Georges on 2024-08-01.
//

#include "ir-enum-type.h"

llvm::Type* IREnumType::getValueType() {
    return this->getType()->getStructElementType(0);
}

bool IREnumType::isEnumType() {
    return true;
}

IREnumType* IREnumType::clone() {
    auto keyTypeMapClone = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : _keyTypeMap) {
        keyTypeMapClone[keyValue.first] = keyValue.second->clone();
    }
    auto clone = new IREnumType(_type, _keyIndexMap, keyTypeMapClone);
    this->initClone(clone);
    return clone;
}