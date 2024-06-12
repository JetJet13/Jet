//
// Created by Johny Georges on 2024-06-12.
//

#include "ir-lookup-table.h"
#include "../../../shared/utils/logger/logger.h"

IRLookupTable::IRLookupTable(std::optional<IRLookupTable*> outerScope) {
    _scope = std::unordered_map<std::string, llvm::Value*>();
    _outerScope = outerScope;
}

IRLookupTable* IRLookupTable::insert(std::string key, llvm::Value* value) {
    _scope.insert(std::pair<std::string, llvm::Value*>(key, value));
    return this;
}

llvm::Value* IRLookupTable::find(std::string key) {
    auto result = _scope.find(key);
    if (result == _scope.end()) {
        if (_outerScope) {
            return _outerScope.value()->find(key);
        }
        throw std::logic_error("no IR Value found for key: " + key);
    } else {
        return result->second;
    }
}

void IRLookupTable::dump() {
    Logger::log("======== IRLookupTable DUMP ========");
    for (auto keyValue : _scope) {
        Logger::log("KEY - ", keyValue.first);
    }
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("===============================================");
}