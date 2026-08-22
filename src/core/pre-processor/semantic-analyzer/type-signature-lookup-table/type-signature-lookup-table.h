//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
#define JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H

#include <unordered_map>
#include "../../../type-signature/type-signature.h"
#include "../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/float-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/char-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/string-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../type-signature/types/function-vararg-type-signature-map/function-vararg-type-signature-map.h"
#include "../types/variable-context/variable-context.h"

class TypeSignatureLookupTable : public std::enable_shared_from_this<TypeSignatureLookupTable> {
private:
    std::string _moduleName;
    std::unordered_map<std::string, std::shared_ptr<TypeSignature>> _typeSignatureLookupTable;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TypeSignature>>> _globalTypeSignatureLookupTable;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>> _globalInvocableTypeSignatureLookupTable;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<FunctionVarArgTypeSignatureMap>>> _globalFunctionOverrideLookupTable;
    std::optional<std::shared_ptr<TypeSignatureLookupTable>> _outerScope;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>> _linkedScopes;
    std::unordered_map<std::string, std::shared_ptr<VariableContext>> _variableContextLookupTable;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<VariableContext>>> _globalVariableContextLookupTable;
    bool _isClassScope = false;
public:
    explicit TypeSignatureLookupTable(std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope = {});
    explicit TypeSignatureLookupTable(std::string moduleName, std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope = {});
    std::shared_ptr<TypeSignatureLookupTable> insert(std::string key, std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobal(std::string key, std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobalInvocable(std::string name, std::shared_ptr<InvocableTypeSignature> typeSignature);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobalFunctionOverride(std::shared_ptr<FunctionVarArgTypeSignatureMap> functionOverrideTypeSignatureMap);
    std::shared_ptr<TypeSignatureLookupTable> insertVariableContext(std::string variableName, std::shared_ptr<VariableContext> variableContext);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobalVariableContext(std::string variableName, std::shared_ptr<VariableContext> variableContext);
    std::string getModuleName();
    void markAsClassScope();
    bool isClassScope();
    void link(std::shared_ptr<TypeSignatureLookupTable> otherScope);
    std::shared_ptr<TypeSignature> find(std::string key);
    std::shared_ptr<TypeSignature> find(std::string moduleId, std::string key);
    std::shared_ptr<TypeSignature> findGlobal(std::string key);
    std::shared_ptr<TypeSignature> findGlobal(std::string moduleId, std::string key);
    std::optional<std::shared_ptr<FunctionVarArgTypeSignatureMap>> findGlobalFunctionOverride(std::string key);
    std::optional<std::shared_ptr<InvocableTypeSignature>> findGlobalFunction(std::string name, std::string key);
    std::optional<std::shared_ptr<InvocableTypeSignature>> findGlobalFunction(std::string moduleId, std::string name, std::string key);
    std::optional<std::shared_ptr<VariableContext>> findVariableContext(std::string variableName);
    std::optional<std::shared_ptr<VariableContext>> findVariableContext(std::string moduleId, std::string variableName);
    std::optional<std::shared_ptr<VariableContext>> findGlobalVariableContext(std::string variableName);
    std::optional<std::shared_ptr<VariableContext>> findGlobalVariableContext(std::string moduleId, std::string variableName);
    std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> getGlobalFunction(std::string name);
    std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> getGlobalFunction(std::string moduleId, std::string name);
    std::unordered_map<std::string, std::shared_ptr<TypeSignature>> getLookupTable();
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TypeSignature>>> getGlobalScope();
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>> getLinkedScopes();
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>> getGlobalInvocableScope();
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<VariableContext>>> getGlobalVariableContext();
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<FunctionVarArgTypeSignatureMap>>> getGlobalOverrideScope();
    void inheritGlobalScope(std::shared_ptr<TypeSignatureLookupTable> otherScope);
    void dumpLinkedScope(std::string moduleId);
    void dump();
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
