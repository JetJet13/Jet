//
// Created by Johny Georges on 2024-06-12.
//

#include "ir-lookup-table.h"
#include "../../shared/utils/logger/logger.h"

IRLookupTable::IRLookupTable(std::optional<IRLookupTable*> outerScope) {
    _globalScope = std::unordered_map<std::string, IRInstructionNode*>();
    _scope = std::unordered_map<std::string, IRInstructionNode*>();
    _loadedScope = std::unordered_map<std::string, IRLoadInstructionNode*>();
    _outerScope = outerScope;
    _typeScope = std::unordered_map<std::string, IRType*>();
}

std::unordered_map<std::string, IRInstructionNode*> IRLookupTable::getGlobalScope() {
    return _globalScope;
}

std::unordered_map<std::string, IRType*> IRLookupTable::getTypeScope() {
    return _typeScope;
}

void IRLookupTable::inherit(IRLookupTable* otherScope) {
    _globalScope = otherScope->getGlobalScope();
    _typeScope = otherScope->getTypeScope();
}

IRLookupTable* IRLookupTable::insert(std::string key, IRInstructionNode* value) {
    _scope[key] = value;
    return this;
}

IRLookupTable* IRLookupTable::insert(std::string key, IRLoadInstructionNode* value) {
    _loadedScope[key] = value;
    return this;
}

IRLookupTable* IRLookupTable::insert(std::string key, IRType* value) {
    _typeScope[key] = value;
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

std::optional<IRInstructionNode*> IRLookupTable::findAcrossScopes(std::string key) {
    auto result = this->find(key);
    if (result) {
        return result;
    }
    return this->findGlobalVariable(key);
}

std::optional<IRType*> IRLookupTable::findType(std::string key) {
    auto result = _typeScope.find(key);
    if (result == _typeScope.end()) {
        if (_outerScope) {
            return _outerScope.value()->findType(key);
        }
        return {};
    } else {
        return result->second;
    }
}

IRLookupTable* IRLookupTable::insertGlobalVariable(std::string key, IRInstructionNode* value) {
    _globalScope[key] = value;
    return this;
}

std::optional<IRInstructionNode*> IRLookupTable::findGlobalVariable(std::string key) {
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

std::vector<IRInstructionNode*> IRLookupTable::getAllInstructionsToFree() {
    auto instructionsToFree = this->getInstructionsToFree();
    if (_outerScope) {
        auto outerInstructionsToFree = _outerScope.value()->getAllInstructionsToFree();
        instructionsToFree.insert(
            instructionsToFree.end(),
            outerInstructionsToFree.begin(),
            outerInstructionsToFree.end()
        );
    }
    return instructionsToFree;
}

std::vector<IRInstructionNode*> IRLookupTable::getInstructionsToFree() {
    auto instructionsToFree = std::vector<IRInstructionNode*>();
    for (auto keyValue : _scope) {
        if (keyValue.second->requiresFreeing()) {
            instructionsToFree.push_back(keyValue.second);
        }
    }
    return instructionsToFree;
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