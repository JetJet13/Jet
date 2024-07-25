//
// Created by Johny Georges on 2024-06-12.
//

#include "ir-lookup-table.h"
#include "../../../shared/utils/logger/logger.h"

IRLookupTable::IRLookupTable(std::optional<IRLookupTable*> outerScope) {
    _globalScope = std::unordered_map<std::string, IRGlobalVariableNode*>();
    _scope = std::unordered_map<std::string, IRAllocationNode*>();
    _outerScope = outerScope;
}

IRLookupTable* IRLookupTable::insert(std::string key, IRAllocationNode* value) {
    _scope.insert(std::pair<std::string, IRAllocationNode*>(key, value));
    return this;
}

std::optional<IRAllocationNode*> IRLookupTable::find(std::string key) {
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

IRLookupTable* IRLookupTable::insertGlobalVariable(std::string key, IRGlobalVariableNode* value) {
    _globalScope.insert(std::pair<std::string, IRGlobalVariableNode*>(key, value));
    return this;
}

std::optional<IRGlobalVariableNode*> IRLookupTable::findGlobalVariable(std::string key) {
    auto result = _globalScope.find(key);
    if (result == _globalScope.end()) {
        if (_outerScope) {
            return _outerScope.value()->findGlobalVariable(key);
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