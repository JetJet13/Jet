//
// Created by Johny Georges on 2024-06-12.
//

#include "ir-lookup-table.h"
#include "../../shared/utils/logger/logger.h"

IRLookupTable::IRLookupTable(std::optional<IRLookupTable*> outerScope) {
    _moduleId = "";
    _globalScope = std::unordered_map<std::string, IRInstructionNode*>();
    _scope = std::unordered_map<std::string, IRInstructionNode*>();
    _arcScope = std::unordered_map<std::string, IRInstructionNode*>();
    _loadedScope = std::unordered_map<std::string, IRLoadInstructionNode*>();
    _outerScope = outerScope;
    _typeScope = std::unordered_map<std::string, IRType*>();
    _globalTypeScope = std::unordered_map<std::string, IRType*>();
    _linkedScopes = new std::unordered_map<std::string, IRLookupTable*>();
}

IRLookupTable::IRLookupTable(std::string moduleId, std::optional<IRLookupTable*> outerScope) {
    _moduleId = moduleId;
    _globalScope = std::unordered_map<std::string, IRInstructionNode*>();
    _scope = std::unordered_map<std::string, IRInstructionNode*>();
    _arcScope = std::unordered_map<std::string, IRInstructionNode*>();
    _loadedScope = std::unordered_map<std::string, IRLoadInstructionNode*>();
    _outerScope = outerScope;
    _typeScope = std::unordered_map<std::string, IRType*>();
    _globalTypeScope = std::unordered_map<std::string, IRType*>();
    _linkedScopes = new std::unordered_map<std::string, IRLookupTable*>();
}

std::unordered_map<std::string, IRInstructionNode*> IRLookupTable::getGlobalScope() {
    return _globalScope;
}

std::unordered_map<std::string, IRType*> IRLookupTable::getTypeScope() {
    return _typeScope;
}

std::unordered_map<std::string, IRType*> IRLookupTable::getGlobalTypeScope() {
    return _globalTypeScope;
}

std::unordered_map<std::string, IRLookupTable*>* IRLookupTable::getLinkedScopes() {
    return _linkedScopes;
}

std::string IRLookupTable::getModuleId() {
    return _moduleId;
}

void IRLookupTable::inherit(IRLookupTable* otherScope) {
    _moduleId = otherScope->getModuleId();
    _globalScope = otherScope->getGlobalScope();
    _typeScope = otherScope->getTypeScope();
    _globalTypeScope = otherScope->getGlobalTypeScope();
    _linkedScopes = otherScope->getLinkedScopes();
}

void IRLookupTable::link(IRLookupTable* otherScope) {
    if (_outerScope) {
        _outerScope.value()->link(otherScope);
    }
    _linkedScopes->insert_or_assign(otherScope->getModuleId(), otherScope);
}

IRLookupTable* IRLookupTable::insert(std::string key, IRInstructionNode* value) {
    _scope[key] = value;
    return this;
}

IRLookupTable* IRLookupTable::insertArc(std::string key, IRInstructionNode* value) {
    _arcScope[key] = value;
    return this;
}


IRLookupTable* IRLookupTable::insert(std::string key, IRLoadInstructionNode* value) {
    _loadedScope[key] = value;
    return this;
}

IRLookupTable* IRLookupTable::insert(std::string key, IRType* value) {
    value->setModuleId(_moduleId);
    _typeScope[key] = value;
    return this;
}

IRLookupTable* IRLookupTable::insertGlobalType(std::string key, IRType* value) {
    value->setModuleId(_moduleId);
    _globalTypeScope[key] = value;
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

std::optional<IRInstructionNode*> IRLookupTable::findArc(std::string key) {
    auto result = _arcScope.find(key);
    if (result == _arcScope.end()) {
        if (_outerScope) {
            return _outerScope.value()->findArc(key);
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

std::optional<IRInstructionNode*> IRLookupTable::findAcrossScopes(std::string moduleId, std::string key) {
    if (moduleId == _moduleId) {
        return this->findAcrossScopes(key);
    }

    if (_outerScope) {
        return _outerScope.value()->findAcrossScopes(moduleId, key);
    }

    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findAcrossScopes(key);
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

std::optional<IRType*> IRLookupTable::findType(std::string moduleId, std::string key) {
    if (moduleId == _moduleId) {
        return this->findType(key);
    }

    if (_outerScope) {
        return _outerScope.value()->findType(moduleId, key);
    }

    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findType(key);
}

std::optional<IRType*> IRLookupTable::findGlobalType(std::string key) {
    auto result = _globalTypeScope.find(key);
    if (result == _globalTypeScope.end()) {
        if (_outerScope) {
            return _outerScope.value()->findGlobalType(key);
        }
        return {};
    } else {
        return result->second;
    }
}

std::optional<IRType*> IRLookupTable::findGlobalType(std::string moduleId, std::string key) {
    if (moduleId == _moduleId) {
        return this->findGlobalType(key);
    }

    if (_outerScope) {
        return _outerScope.value()->findGlobalType(moduleId, key);
    }

    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findGlobalType(key);
}

IRLookupTable* IRLookupTable::insertGlobalVariable(std::string key, IRInstructionNode* value) {
    _globalScope[key] = value;
    if (_outerScope) {
        _outerScope.value()->insertGlobalVariable(key, value);
    }
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

std::optional<IRInstructionNode*> IRLookupTable::findGlobalVariable(std::string moduleId, std::string key) {
    if (moduleId == _moduleId) {
        return this->findGlobalVariable(key);
    }

    if (_outerScope) {
        return _outerScope.value()->findGlobalVariable(moduleId, key);
    }

    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findGlobalVariable(key);
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
    for (auto keyValue : _arcScope) {
        Logger::log("ARC KEY - ", keyValue.first);
    }
    for (auto keyValue : *_linkedScopes) {
        Logger::log("LINKED MODULE - ", keyValue.first);
    }
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("===============================================");
}