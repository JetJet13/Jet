//
// Created by Johny Georges on 2024-06-12.
//

#include "ir-lookup-table.h"
#include "../../../shared/utils/logger/logger.h"

IRLookupTable::IRLookupTable(std::optional<IRLookupTable*> outerScope) {
    _scope = std::unordered_map<std::string, llvm::AllocaInst*>();
    _outerScope = outerScope;
}

IRLookupTable* IRLookupTable::insert(std::string key, llvm::AllocaInst* value) {
    _scope.insert(std::pair<std::string, llvm::AllocaInst*>(key, value));
    return this;
}

std::optional<llvm::AllocaInst*> IRLookupTable::find(std::string key) {
    auto result = _scope.find(key);
    if (result == _scope.end()) {
        if (_outerScope) {
            return _outerScope.value()->find(key);
        }
        return {};
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