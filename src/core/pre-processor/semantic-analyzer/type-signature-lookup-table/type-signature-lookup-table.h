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

class TypeSignatureLookupTable : public std::enable_shared_from_this<TypeSignatureLookupTable> {
private:
    std::string _moduleName;
    std::unordered_map<std::string, TypeSignature*> _typeSignatureLookupTable;
    std::unordered_map<std::string, TypeSignature*>* _globalTypeSignatureLookupTable;
    std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>* _globalInvocableTypeSignatureLookupTable;
    std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* _globalFunctionOverrideLookupTable;
    std::optional<std::shared_ptr<TypeSignatureLookupTable>> _outerScope;
    std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>* _linkedScopes;
public:
    explicit TypeSignatureLookupTable(std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope = {});
    explicit TypeSignatureLookupTable(std::string moduleName, std::optional<std::shared_ptr<TypeSignatureLookupTable>> outerScope = {});
    std::shared_ptr<TypeSignatureLookupTable> insert(std::string key, TypeSignature* typeSignature);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobal(std::string key, TypeSignature* typeSignature);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobalInvocable(std::string name, InvocableTypeSignature* typeSignature);
    std::shared_ptr<TypeSignatureLookupTable> insertGlobalFunctionOverride(FunctionVarArgTypeSignatureMap* functionOverrideTypeSignatureMap);
    std::string getModuleName();
    void link(std::shared_ptr<TypeSignatureLookupTable> otherScope);
    TypeSignature* find(std::string key);
    TypeSignature* find(std::string moduleId, std::string key);
    TypeSignature* findGlobal(std::string key);
    TypeSignature* findGlobal(std::string moduleId, std::string key);
    std::optional<FunctionVarArgTypeSignatureMap*> findGlobalFunctionOverride(std::string key);
    std::optional<InvocableTypeSignature*> findGlobalFunction(std::string name, std::string key);
    std::optional<InvocableTypeSignature*> findGlobalFunction(std::string moduleId, std::string name, std::string key);
    std::optional<std::unordered_map<std::string, InvocableTypeSignature*>*> getGlobalFunction(std::string name);
    std::optional<std::unordered_map<std::string, InvocableTypeSignature*>*> getGlobalFunction(std::string moduleId, std::string name);
    std::unordered_map<std::string, TypeSignature*> getLookupTable();
    std::unordered_map<std::string, TypeSignature*>* getGlobalScope();
    std::unordered_map<std::string, std::shared_ptr<TypeSignatureLookupTable>>* getLinkedScopes();
    std::unordered_map<std::string, std::unordered_map<std::string, InvocableTypeSignature*>*>* getGlobalInvocableScope();
    std::unordered_map<std::string, FunctionVarArgTypeSignatureMap*>* getGlobalOverrideScope();
    void inheritGlobalScope(std::shared_ptr<TypeSignatureLookupTable> otherScope);
    void dumpLinkedScope(std::string moduleId);
    void dump();
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_H
