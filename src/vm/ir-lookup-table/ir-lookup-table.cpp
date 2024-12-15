//
// Created by Johny Georges on 2024-06-12.
//

#include "ir-lookup-table.h"
#include "../../shared/utils/logger/logger.h"

IRLookupTable::IRLookupTable(std::optional<IRLookupTable*> outerScope) {
    _globalScope = std::unordered_map<std::string, IRGlobalVariableNode*>();
    _scope = std::unordered_map<std::string, IRInstructionNode*>();
    _loadedScope = std::unordered_map<std::string, IRLoadInstructionNode*>();
    _outerScope = outerScope;
}

std::unordered_map<std::string, IRGlobalVariableNode*> IRLookupTable::getGlobalScope() {
    return _globalScope;
}

void IRLookupTable::inheritGlobalScope(IRLookupTable* otherScope) {
    _globalScope = otherScope->getGlobalScope();
}

IRLookupTable* IRLookupTable::insert(std::string key, IRInstructionNode* value) {
    _scope[key] = value;
    return this;
}

IRLookupTable* IRLookupTable::insert(std::string key, IRLoadInstructionNode* value) {
    _loadedScope[key] = value;
    return this;
}

std::optional<IRInstructionNode*> IRLookupTable::find(std::string key) {
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

std::optional<IRLoadInstructionNode*> IRLookupTable::findLoaded(std::string key) {
    auto result = _loadedScope.find(key);
    if (result == _loadedScope.end()) {
        if (_outerScope) {
            return _outerScope.value()->findLoaded(key);
        }
        return {};
    } else {
        return result->second;
    }
}

std::optional<IRNode*> IRLookupTable::findAcrossScopes(std::string key) {
    auto result = this->find(key);
    if (result) {
        return result;
    }
    auto loadedResult = this->findLoaded(key);
    if (loadedResult) {
        return loadedResult;
    }
    return this->findGlobalVariable(key);
}

IRLookupTable* IRLookupTable::insertGlobalVariable(std::string key, IRGlobalVariableNode* value) {
    _globalScope[key] = value;
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

std::optional<IRInstructionNode*> IRLookupTable::getClassScope() {
    return this->find("jet.class.scope");
}

void IRLookupTable::dump() {
    Logger::log("======== IRLookupTable DUMP ========");
    for (auto keyValue : _scope) {
        Logger::log("KEY - ", keyValue.first);
    }
    for (auto keyValue : _loadedScope) {
        Logger::log("LOADED KEY - ", keyValue.first);
    }
    for (auto keyValue : _globalScope) {
        Logger::log("GLOBAL KEY - ", keyValue.first);
    }
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("===============================================");
}