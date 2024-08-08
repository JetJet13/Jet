//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-struct-type.h"
#include "../../shared/utils/logger/logger.h"

IRStructType::IRStructType(llvm::StructType *type, std::unordered_map<std::string, unsigned long> keyIndexMap, std::unordered_map<std::string, IRType*> keyTypeMap) : IRType(type) {
    _type = type;
    _keyIndexMap = keyIndexMap;
    _keyTypeMap = keyTypeMap;
}

llvm::StructType* IRStructType::getType() {
    return _type;
}

unsigned long IRStructType::getIndexForKey(std::string key) {
    Logger::log("getIndexForKey::key", key);
    auto result = _keyIndexMap.find(key);
    if (result == _keyIndexMap.end()) {
        throw std::logic_error("no struct index found for key: " + key);
    } else {
        return result->second;
    }
}

unsigned long IRStructType::getIndexForKey(unsigned long indexAsKey) {
    return this->getIndexForKey(std::to_string(indexAsKey));
}

IRType* IRStructType::getIRTypeForKey(std::string key) {
    auto result = _keyTypeMap.find(key);
    if (result == _keyTypeMap.end()) {
        throw std::logic_error("no type found for key: " + key);
    } else {
        return result->second;
    }
}

IRType* IRStructType::getIRTypeForKey(unsigned long indexAsKey) {
    return this->getIRTypeForKey(std::to_string(indexAsKey));
}

void IRStructType::replaceIRTypeAtKey(std::string key, IRType* newIRType) {
    this->_keyTypeMap.insert(std::pair<std::string, IRType*>(key, newIRType));
}

void IRStructType::print() {
    llvm::outs().write_escaped("|");
    _type->print(llvm::outs(), true, true);
    llvm::outs().write_escaped("|");
    for (auto keyValue : _keyTypeMap) {
        llvm::outs().write_escaped("|");
        llvm::outs().write_escaped(keyValue.first);
        llvm::outs().write_escaped(" : ");
        keyValue.second->print();
        llvm::outs().write_escaped("|");
    }
    llvm::outs().write_escaped("|");
    for (const auto& keyValue : _keyIndexMap) {
        llvm::outs().write_escaped("|");
        llvm::outs().write_escaped(keyValue.first);
        llvm::outs().write_escaped(" : ");
        llvm::outs().write_escaped(std::to_string(keyValue.second));
        llvm::outs().write_escaped("|");
    }
}
