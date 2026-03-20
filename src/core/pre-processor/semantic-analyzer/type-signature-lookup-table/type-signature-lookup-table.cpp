//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../../../type-signature/literal-type-signature/types/literal-type-signature-name.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"


TypeSignatureLookupTable::TypeSignatureLookupTable(std::optional<TypeSignatureLookupTable*> outerScope) {
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    _globalTypeSignatureLookupTable = new std::unordered_map<std::string, TypeSignature*>();
    _globalInvocableTypeSignatureLookupTable = new std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>();
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

TypeSignatureLookupTable* TypeSignatureLookupTable::insertGlobalInvocable(std::string name, InvocableTypeSignature* typeSignature) {
    auto key = FunctionIdGenerator::generateFor(typeSignature);
    auto existing = _globalInvocableTypeSignatureLookupTable->find(name);
    if (existing == _globalInvocableTypeSignatureLookupTable->end()) {
        auto invocableTypeSignatureLookupTable = new std::unordered_map<std::string, InvocableTypeSignature*>();
        invocableTypeSignatureLookupTable->insert(std::pair(key, typeSignature));
        _globalInvocableTypeSignatureLookupTable->insert(std::pair(name, invocableTypeSignatureLookupTable));
    } else {
        existing->second->insert(std::pair(key, typeSignature));
    }
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

std::optional<InvocableTypeSignature*> TypeSignatureLookupTable::findGlobalFunction(std::string name, std::string key) {
    auto globalFunction = _globalInvocableTypeSignatureLookupTable->find(name);
    if (globalFunction == _globalInvocableTypeSignatureLookupTable->end()) {
        return {};
    }

    auto result = globalFunction->second->find(key);
    if (result == globalFunction->second->end()) {
        return {};
    }
    return result->second;
}

std::optional<std::unordered_map<std::string, InvocableTypeSignature*>*> TypeSignatureLookupTable::getGlobalFunction(std::string name) {
    auto globalFunction = _globalInvocableTypeSignatureLookupTable->find(name);
    if (globalFunction == _globalInvocableTypeSignatureLookupTable->end()) {
        return {};
    }
    return globalFunction->second;
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

std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>* TypeSignatureLookupTable::getGlobalInvocableScope() {
    return _globalInvocableTypeSignatureLookupTable;
}

std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* TypeSignatureLookupTable::getGlobalOverrideScope() {
    return _globalFunctionOverrideLookupTable;
}

void TypeSignatureLookupTable::inheritGlobalScope(TypeSignatureLookupTable* otherScope) {
    _globalTypeSignatureLookupTable = otherScope->getGlobalScope();
    _globalFunctionOverrideLookupTable = otherScope->getGlobalOverrideScope();
    _globalInvocableTypeSignatureLookupTable = otherScope->getGlobalInvocableScope();
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
    for (auto keyValue : *_globalInvocableTypeSignatureLookupTable) {
        Logger::log("NAME - ", keyValue.first);
        for (auto invocableLookup : *keyValue.second) {
            Logger::log("  KEY - ", invocableLookup.first, "VALUE - ", invocableLookup.second->toString());
        }
    }
    for (auto keyValue : *_globalFunctionOverrideLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    Logger::log("===============================================");
}
