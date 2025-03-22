//
// Created by Johny Georges on 2025-03-22.
//

#include "ast-lookup-table.h"
#include "../../shared/utils/logger/logger.h"

ASTLookupTable::ASTLookupTable(std::optional<ASTLookupTable*> outerScope) {
    _globalScope = std::unordered_map<std::string, ASTDeclarationNode*>();
    _scope = std::unordered_map<std::string, ASTDeclarationNode*>();
    _childScopes = std::unordered_map<std::string, ASTLookupTable*>();
    _outerScope = outerScope;
}

std::unordered_map<std::string, ASTDeclarationNode*> ASTLookupTable::getGlobalScope() {
    return _globalScope;
}

void ASTLookupTable::inherit(ASTLookupTable* otherScope) {
    _globalScope = otherScope->getGlobalScope();
}

ASTLookupTable* ASTLookupTable::insert(std::string key, ASTDeclarationNode* value) {
    _scope[key] = value;
    return this;
}

std::optional<ASTDeclarationNode*> ASTLookupTable::find(std::string key) {
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

std::optional<ASTDeclarationNode*> ASTLookupTable::findAcrossScopes(std::string key) {
    auto result = this->find(key);
    if (result) {
        return result;
    }
    return this->findGlobalVariable(key);
}

ASTLookupTable* ASTLookupTable::insertGlobalVariable(std::string key, ASTDeclarationNode* value) {
    _globalScope[key] = value;
    return this;
}

ASTLookupTable* ASTLookupTable::insertChildScope(std::string key, ASTLookupTable* value) {
    _childScopes[key] = value;
    return this;
}

std::optional<ASTDeclarationNode*> ASTLookupTable::findGlobalVariable(std::string key) {
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

std::optional<ASTLookupTable*> ASTLookupTable::findChildScope(std::string key) {
    auto result = _childScopes.find(key);
    if (result == _childScopes.end()) {
        return {};
    } else {
        return result->second;
    }
}

void ASTLookupTable::dump() {
    Logger::log("======== ASTLookupTable DUMP ========");
    for (auto keyValue : _scope) {
        Logger::log("KEY - ", keyValue.first);
    }
    for (auto keyValue : _globalScope) {
        Logger::log("GLOBAL KEY - ", keyValue.first);
    }
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("===============================================");
}