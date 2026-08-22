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
    _typeSignatureLookupTable = std::unordered_map<std::string, std::shared_ptr<TypeSignature>>();
    _globalTypeSignatureLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<TypeSignature>>>();
    _globalInvocableTypeSignatureLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>>();
    _globalFunctionOverrideLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<FunctionVarArgTypeSignatureMap>>>();
    _outerScope = outerScope;
    _linkedScopes = std::make_shared<std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>>();
    _variableContextLookupTable = std::unordered_map<std::string, std::shared_ptr<VariableContext>>();
    _globalVariableContextLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<VariableContext>>>();
}

TypeSignatureLookupTable::TypeSignatureLookupTable(std::string moduleName, std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope) {
    _moduleName = moduleName;
    _typeSignatureLookupTable = std::unordered_map<std::string, std::shared_ptr<TypeSignature>>();
    _globalTypeSignatureLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<TypeSignature>>>();
    _globalInvocableTypeSignatureLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>>();
    _globalFunctionOverrideLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<FunctionVarArgTypeSignatureMap>>>();
    _outerScope = outerScope;
    _linkedScopes = std::make_shared<std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>>();
    _variableContextLookupTable = std::unordered_map<std::string, std::shared_ptr<VariableContext>>();
    _globalVariableContextLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<VariableContext>>>();
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insert(std::string key, std::shared_ptr<TypeSignature> typeSignature) {
    typeSignature->setModuleId(this->getModuleName());
    _typeSignatureLookupTable.insert(std::pair(key, typeSignature));
    return std::dynamic_pointer_cast<TypeSignatureLookupTable>(shared_from_this());
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobal(std::string key, std::shared_ptr<TypeSignature> typeSignature) {
    typeSignature->setModuleId(this->getModuleName());
    _globalTypeSignatureLookupTable->insert_or_assign(key, typeSignature);
    return std::dynamic_pointer_cast<TypeSignatureLookupTable>(shared_from_this());
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobalInvocable(std::string name, std::shared_ptr<InvocableTypeSignature> typeSignature) {
    typeSignature->setModuleId(this->getModuleName());
    auto key = FunctionIdGenerator::generateFor(typeSignature);
    auto existing = _globalInvocableTypeSignatureLookupTable->find(name);
    if (existing == _globalInvocableTypeSignatureLookupTable->end()) {
        auto invocableTypeSignatureLookupTable = std::make_shared<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>();
        invocableTypeSignatureLookupTable->insert_or_assign(key, typeSignature);
        _globalInvocableTypeSignatureLookupTable->insert_or_assign(name, invocableTypeSignatureLookupTable);
    } else {
        existing->second->insert_or_assign(key, typeSignature);
    }
    return std::dynamic_pointer_cast<TypeSignatureLookupTable>(shared_from_this());
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobalFunctionOverride(std::shared_ptr<FunctionVarArgTypeSignatureMap> functionOverrideTypeSignatureMap) {
    _globalFunctionOverrideLookupTable->insert_or_assign(
            functionOverrideTypeSignatureMap->getFunctionName(),
            functionOverrideTypeSignatureMap
    );
    return std::dynamic_pointer_cast<TypeSignatureLookupTable>(shared_from_this());
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertVariableContext(std::string variableName, std::shared_ptr<VariableContext> variableContext) {
    _variableContextLookupTable.insert_or_assign(
            variableName,
            variableContext
    );
    return std::dynamic_pointer_cast<TypeSignatureLookupTable>(shared_from_this());
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTable::insertGlobalVariableContext(std::string variableName, std::shared_ptr<VariableContext> variableContext) {
    _globalVariableContextLookupTable->insert_or_assign(
            variableName,
            variableContext
    );
    return std::dynamic_pointer_cast<TypeSignatureLookupTable>(shared_from_this());
}

std::string TypeSignatureLookupTable::getModuleName() {
    if (_outerScope) {
        return _outerScope.value()->getModuleName();
    }
    return _moduleName;
}

void TypeSignatureLookupTable::markAsClassScope() {
    _isClassScope = true;
}

bool TypeSignatureLookupTable::isClassScope() {
    return _isClassScope;
}

void TypeSignatureLookupTable::link(std::shared_ptr<TypeSignatureLookupTable> otherScope) {
    if (_outerScope) {
        _outerScope.value()->link(otherScope);
        return;
    }
    _linkedScopes->insert_or_assign(otherScope->getModuleName(), otherScope);
}

std::shared_ptr<TypeSignature> TypeSignatureLookupTable::find(std::string key) {
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

std::shared_ptr<TypeSignature> TypeSignatureLookupTable::find(std::string moduleId, std::string key) {
    if (moduleId == _moduleName) {
        return this->find(key);
    }
    if (_outerScope) {
        return _outerScope.value()->find(moduleId, key);
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return std::make_shared<UnknownTypeSignature>();
    }
    return scope->second->find(key);
}

std::shared_ptr<TypeSignature> TypeSignatureLookupTable::findGlobal(std::string key) {
    auto result = _globalTypeSignatureLookupTable->find(key);
    if (result == _globalTypeSignatureLookupTable->end()) {
        return std::make_shared<UnknownTypeSignature>();
    } else {
        return result->second;
    }
}

std::shared_ptr<TypeSignature> TypeSignatureLookupTable::findGlobal(std::string moduleId, std::string key) {
    if (moduleId == _moduleName) {
        return this->findGlobal(key);
    }
    if (_outerScope) {
        return _outerScope.value()->findGlobal(moduleId, key);
    }
    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return std::make_shared<UnknownTypeSignature>();
    }
    return scope->second->findGlobal(key);
}

std::optional<std::shared_ptr<FunctionVarArgTypeSignatureMap>> TypeSignatureLookupTable::findGlobalFunctionOverride(std::string key) {
    auto result = _globalFunctionOverrideLookupTable->find(key);
    if (result == _globalFunctionOverrideLookupTable->end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<std::shared_ptr<InvocableTypeSignature>> TypeSignatureLookupTable::findGlobalFunction(std::string name, std::string key) {
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

std::optional<std::shared_ptr<InvocableTypeSignature>> TypeSignatureLookupTable::findGlobalFunction(std::string moduleId, std::string name, std::string key) {
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

std::optional<std::shared_ptr<VariableContext>> TypeSignatureLookupTable::findVariableContext(std::string variableName) {
    auto result = _variableContextLookupTable.find(variableName);
    if (result == _variableContextLookupTable.end()) {
        if (_outerScope) {
            return _outerScope.value()->findVariableContext(variableName);
        }
        return this->findGlobalVariableContext(variableName);
    } else {
        return result->second;
    }
}

std::optional<std::shared_ptr<VariableContext>> TypeSignatureLookupTable::findVariableContext(std::string moduleId, std::string variableName) {
    if (moduleId == _moduleName) {
        return this->findVariableContext(variableName);
    }

    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findVariableContext(variableName);
}

std::optional<std::shared_ptr<VariableContext>> TypeSignatureLookupTable::findGlobalVariableContext(std::string variableName) {
    auto result = _globalVariableContextLookupTable->find(variableName);
    if (result == _globalVariableContextLookupTable->end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<std::shared_ptr<VariableContext>> TypeSignatureLookupTable::findGlobalVariableContext(std::string moduleId, std::string variableName) {
    if (moduleId == _moduleName) {
        return this->findGlobalVariableContext(variableName);
    }

    auto scope = _linkedScopes->find(moduleId);
    if (scope == _linkedScopes->end()) {
        return {};
    }
    return scope->second->findGlobalVariableContext(variableName);
}

std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> TypeSignatureLookupTable::getGlobalFunction(std::string name) {
    auto globalFunction = _globalInvocableTypeSignatureLookupTable->find(name);
    if (globalFunction == _globalInvocableTypeSignatureLookupTable->end()) {
        return {};
    }
    return globalFunction->second;
}

std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> TypeSignatureLookupTable::getGlobalFunction(std::string moduleId, std::string name) {
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

std::unordered_map<std::string, std::shared_ptr<TypeSignature>> TypeSignatureLookupTable::getLookupTable() {
    auto lookupTable = std::unordered_map<std::string, std::shared_ptr<TypeSignature>>();
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

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TypeSignature>>> TypeSignatureLookupTable::getGlobalScope() {
    return _globalTypeSignatureLookupTable;
}

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>> TypeSignatureLookupTable::getLinkedScopes() {
    return _linkedScopes;
}

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>> TypeSignatureLookupTable::getGlobalInvocableScope() {
    return _globalInvocableTypeSignatureLookupTable;
}

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<VariableContext>>> TypeSignatureLookupTable::getGlobalVariableContext() {
    return _globalVariableContextLookupTable;
}

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<FunctionVarArgTypeSignatureMap>>> TypeSignatureLookupTable::getGlobalOverrideScope() {
    return _globalFunctionOverrideLookupTable;
}

void TypeSignatureLookupTable::inheritGlobalScope(std::shared_ptr<TypeSignatureLookupTable> otherScope) {
    _linkedScopes = otherScope->getLinkedScopes();
    _globalTypeSignatureLookupTable = otherScope->getGlobalScope();
    _globalFunctionOverrideLookupTable = otherScope->getGlobalOverrideScope();
    _globalInvocableTypeSignatureLookupTable = otherScope->getGlobalInvocableScope();
    _globalVariableContextLookupTable = otherScope->getGlobalVariableContext();
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
    for (auto keyValue : _variableContextLookupTable) {
        Logger::log("VARIABLE CONTEXT KEY - ", keyValue.first);
    }
    Logger::log("======== OUTER SCOPE DUMP ========");
    if (_outerScope) {
        _outerScope.value()->dump();
    }
    Logger::log("======== GLOBAL SCOPE DUMP ========");
    for (auto keyValue : *_globalTypeSignatureLookupTable) {
        Logger::log("KEY - ", keyValue.first, "VALUE - ", keyValue.second->toString());
    }
    for (auto keyValue : *_globalVariableContextLookupTable) {
        Logger::log("GLOBAL VARIABLE CONTEXT KEY - ", keyValue.first);
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
