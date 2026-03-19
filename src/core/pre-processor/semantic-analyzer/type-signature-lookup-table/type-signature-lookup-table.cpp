//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../../../type-signature/literal-type-signature/types/literal-type-signature-name.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"


TypeSignatureLookupTable::TypeSignatureLookupTable(std::optional<TypeSignatureLookupTable*> outerScope) {
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    _globalTypeSignatureLookupTable = new std::unordered_map<std::string, TypeSignature*>();
    _globalFunctionOverrideLookupTable = new std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>();
    _outerScope = outerScope;
}

TypeSignatureLookupTable* TypeSignatureLookupTable::insert(std::string key, TypeSignature* typeSignature) {
    _typeSignatureLookupTable.insert(std::pair(key, typeSignature));
    return this;
}

TypeSignatureLookupTable* TypeSignatureLookupTable::insertGlobal(std::string key, TypeSignature* typeSignature) {
    _globalTypeSignatureLookupTable->insert(std::pair(key, typeSignature));
    return this;
}

TypeSignatureLookupTable* TypeSignatureLookupTable::insertGlobalFunctionOverride(FunctionVarArgTypeSignatureMap* functionOverrideTypeSignatureMap) {
    _globalFunctionOverrideLookupTable->insert(
            std::pair(
                functionOverrideTypeSignatureMap->getFunctionName(),
                functionOverrideTypeSignatureMap
            )
    );
    return this;
}

TypeSignature* TypeSignatureLookupTable::find(std::string key) {
    auto result = _typeSignatureLookupTable.find(key);
    if (result == _typeSignatureLookupTable.end()) {
        if (_outerScope) {
            return _outerScope.value()->find(key);
        }
        return this->findGlobal(key);
    } else {
        return result->second;
    }
}

TypeSignature* TypeSignatureLookupTable::findGlobal(std::string key) {
    auto result = _globalTypeSignatureLookupTable->find(key);
    if (result == _globalTypeSignatureLookupTable->end()) {
        return new UnknownTypeSignature();
    } else {
        return result->second;
    }
}

std::optional<FunctionVarArgTypeSignatureMap*> TypeSignatureLookupTable::findGlobalFunctionOverride(std::string key) {
    auto result = _globalFunctionOverrideLookupTable->find(key);
    if (result == _globalFunctionOverrideLookupTable->end()) {
        return {};
    } else {
        return result->second;
    }
}

std::unordered_map<std::string, TypeSignature*> TypeSignatureLookupTable::getLookupTable() {
    auto lookupTable = std::unordered_map<std::string, TypeSignature*>();
    if (_outerScope) {
        for (auto keyValue : _outerScope.value()->getLookupTable()) {
            lookupTable[keyValue.first] = keyValue.second;
        }
    }
    for (auto keyValue : _typeSignatureLookupTable) {
        lookupTable[keyValue.first] = keyValue.second;
    }
    return lookupTable;
}

std::unordered_map<std::string, TypeSignature*>* TypeSignatureLookupTable::getGlobalScope() {
    return _globalTypeSignatureLookupTable;
}

std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* TypeSignatureLookupTable::getGlobalOverrideScope() {
    return _globalFunctionOverrideLookupTable;
}

void TypeSignatureLookupTable::inheritGlobalScope(TypeSignatureLookupTable* otherScope) {
    _globalTypeSignatureLookupTable = otherScope->getGlobalScope();
    _globalFunctionOverrideLookupTable = otherScope->getGlobalOverrideScope();
}

void TypeSignatureLookupTable::dump() {
    Logger::log("======== TypeSignatureLookupTable DUMP ========");
    for (auto keyValue : _typeSignatureLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    Logger::log("======== OUTER SCOPE DUMP ========");
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("======== GLOBAL SCOPE DUMP ========");
    for (auto keyValue : *_globalTypeSignatureLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    for (auto keyValue : *_globalFunctionOverrideLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    Logger::log("===============================================");
}
