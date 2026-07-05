//
// Created by Johny Georges on 2024-08-01.
//

#include "ir-enum-type.h"

llvm::Type* IREnumType::getValueType() {
    return this->getType()->getStructElementType(0);
}

bool IREnumType::containsTypeThatRequiresFreeing() {
    return false;
}

bool IREnumType::isEnumType() {
    return true;
}

std::shared_ptr<IRType> IREnumType::clone() {
    auto keyTypeMapClone = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (auto keyValue : _keyTypeMap) {
        keyTypeMapClone[keyValue.first] = keyValue.second->clone();
    }
    auto clone = std::make_shared<IREnumType>(_type, _keyIndexMap, _keyIdMap, keyTypeMapClone);
    this->initClone(clone);
    return clone;
}