//
// Created by Johny Georges on 2024-05-03.
//

#include "type-signature-lookup-table.h"
#include "../../../type-signature/literal-type-signature/types/literal-type-signature-name.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"

TypeSignatureLookupTable::TypeSignatureLookupTable(std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope) {
    _moduleName = "";
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    _globalTypeSignatureLookupTable = new std::unordered_map<std::string, TypeSignature*>();
    _globalInvocableTypeSignatureLookupTable = new std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>();
    _globalFunctionOverrideLookupTable = new std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>();
    _outerScope = outerScope;
    _linkedScopes = new std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>();
}

TypeSignatureLookupTable::TypeSignatureLookupTable(std::string moduleName, std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope) {
    _moduleName = moduleName;
    _typeSignatureLookupTable = std::unordered_map<std::string, TypeSignature*>();
    _globalTypeSignatureLookupTable = new std::unordered_map<std::string, TypeSignature*>();
    _globalInvocableTypeSignatureLookupTable = new std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>();
    _globalFunctionOverrideLookupTable = new std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>();
    _outerScope = outerScope;
    _linkedScopes = new std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>();
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insert(std::string key, TypeSignature* typeSignature) {
    typeSignature->setModuleId(this->getModuleName());
    _typeSignatureLookupTable.insert(std::pair(key, typeSignature));
    return shared_from_this();
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobal(std::string key, TypeSignature* typeSignature) {
    typeSignature->setModuleId(this->getModuleName());
    _globalTypeSignatureLookupTable->insert_or_assign(key, typeSignature);
    return shared_from_this();
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobalInvocable(std::string name, InvocableTypeSignature* typeSignature) {
    typeSignature->setModuleId(this->getModuleName());
    auto key = FunctionIdGenerator::generateFor(typeSignature);
    auto existing = _globalInvocableTypeSignatureLookupTable->find(name);
    if (existing == _globalInvocableTypeSignatureLookupTable->end()) {
        auto invocableTypeSignatureLookupTable = new std::unordered_map<std::string, InvocableTypeSignature*>();
        invocableTypeSignatureLookupTable->insert_or_assign(key, typeSignature);
        _globalInvocableTypeSignatureLookupTable->insert_or_assign(name, invocableTypeSignatureLookupTable);
    } else {
        existing->second->insert_or_assign(key, typeSignature);
    }
    return shared_from_this();
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobalFunctionOverride(FunctionVarArgTypeSignatureMap* functionOverrideTypeSignatureMap) {
    _globalFunctionOverrideLookupTable->insert_or_assign(
            functionOverrideTypeSignatureMap->getFunctionName(),
            functionOverrideTypeSignatureMap
    );
    return shared_from_this();
}

std::string TypeSignatureLookupTable::getModuleName() {
    if (_outerScope) {
        return _outerScope.value()->getModuleName();
    }
    return _moduleName;
}

void TypeSignatureLookupTable::link(std::shared_ptr<TypeSignatureLookupTable> otherScope) {
    if (_outerScope) {
        _outerScope.value()->link(otherScope);
        return;
    }
    _linkedScopes->insert_or_assign(otherScope->getModuleName(), otherScope);
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

TypeSignature* TypeSignatureLookupTable::find(std::string moduleId, std::string key) {
    if (moduleId == _moduleName) {
        return this->find(key);
    }
    if (_outerScope) {
        return _outerScope.value()->find(moduleId, key);
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return new UnknownTypeSignature();
    }
    return scope->second->find(key);
}

TypeSignature* TypeSignatureLookupTable::findGlobal(std::string key) {
    auto result = _globalTypeSignatureLookupTable->find(key);
    if (result == _globalTypeSignatureLookupTable->end()) {
        return new UnknownTypeSignature();
    } else {
        return result->second;
    }
}

TypeSignature* TypeSignatureLookupTable::findGlobal(std::string moduleId, std::string key) {
    if (moduleId == _moduleName) {
        return this->findGlobal(key);
    }
    if (_outerScope) {
        return _outerScope.value()->findGlobal(moduleId, key);
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return new UnknownTypeSignature();
    }
    return scope->second->findGlobal(key);
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

std::optional<InvocableTypeSignature*> TypeSignatureLookupTable::findGlobalFunction(std::string moduleId, std::string name, std::string key) {
    if (moduleId == _moduleName) {
        return this->findGlobalFunction(name, key);
    }
    if (_outerScope) {
        return _outerScope.value()->findGlobalFunction(moduleId, name, key);
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findGlobalFunction(name, key);
}

std::optional<std::unordered_map<std::string, InvocableTypeSignature*>*> TypeSignatureLookupTable::getGlobalFunction(std::string name) {
    auto globalFunction = _globalInvocableTypeSignatureLookupTable->find(name);
    if (globalFunction == _globalInvocableTypeSignatureLookupTable->end()) {
        return {};
    }
    return globalFunction->second;
}

std::optional<std::unordered_map<std::string, InvocableTypeSignature*>*> TypeSignatureLookupTable::getGlobalFunction(std::string moduleId, std::string name) {
    if (moduleId == _moduleName) {
        return this->getGlobalFunction(name);
    }
    if (_outerScope) {
        return _outerScope.value()->getGlobalFunction(moduleId, name);
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->getGlobalFunction(name);
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

std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>* TypeSignatureLookupTable::getLinkedScopes() {
    return _linkedScopes;
}

std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>* TypeSignatureLookupTable::getGlobalInvocableScope() {
    return _globalInvocableTypeSignatureLookupTable;
}

std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* TypeSignatureLookupTable::getGlobalOverrideScope() {
    return _globalFunctionOverrideLookupTable;
}

void TypeSignatureLookupTable::inheritGlobalScope(std::shared_ptr<TypeSignatureLookupTable> otherScope) {
    _linkedScopes = otherScope->getLinkedScopes();
    _globalTypeSignatureLookupTable = otherScope->getGlobalScope();
    _globalFunctionOverrideLookupTable = otherScope->getGlobalOverrideScope();
    _globalInvocableTypeSignatureLookupTable = otherScope->getGlobalInvocableScope();
}

void TypeSignatureLookupTable::dumpLinkedScope(std::string moduleId) {
    if (_outerScope) {
        _outerScope.value()->dumpLinkedScope(moduleId);
        return;
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        Logger::log("unable to dump linked scope; Not Found:", moduleId);
        return;
    }
    return scope->second->dump();
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
    Logger::log("======== LINKED SCOPES DUMP ========");
    for (auto keyValue : *_linkedScopes) {
        Logger::log("MODULE ID - ", keyValue.first);
    }
    Logger::log("===============================================");
}
