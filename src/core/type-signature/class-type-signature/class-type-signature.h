// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_H
#define JETLANG_CLASS_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "../../lexeme/lexeme.h"
#include "class-property-type-signature/class-property-type-signature.h"
#include "class-method-type-signature/class-method-type-signature.h"
#include "class-constructor-type-signature/class-constructor-type-signature.h"
#include "../types/type-signature-map/type-signature-map.h"
#include "../interface-type-signature/interface-type-signature.h"

class ClassTypeSignature : public TypeSignature {
private:
    TypeSignatureMap<std::shared_ptr<ClassConstructorTypeSignature>> _constructors;
    TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>> _staticProperties;
    TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>> _instanceProperties;
    TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>> _staticMethods;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>> _staticMethodLookupTable;
    TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>> _instanceMethods;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>>> _instanceMethodLookupTable;
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _implements;
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _interface;
    std::shared_ptr<ParameterListItemTypeSignature> _classScopeParameter;
public:
    ClassTypeSignature();
    std::shared_ptr<ParameterListItemTypeSignature> getClassScopeParameter();
    TypeSignatureMap<std::shared_ptr<ClassConstructorTypeSignature>>* getConstructors();
    TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>* getStaticProperties();
    TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>* getInstanceProperties();
    TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>* getStaticMethods();
    TypeSignatureMap<std::shared_ptr<ClassMethodTypeSignature>>* getInstanceMethods();
    std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> findInstanceMethodsByName(std::string name);
    std::optional<std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<InvocableTypeSignature>>>> findStaticMethodsByName(std::string name);
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getImplements();
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getInterface();
    std::shared_ptr<ClassTypeSignature> addConstructor(std::string key, std::shared_ptr<ClassConstructorTypeSignature> classConstructorTypeSignature);
    std::shared_ptr<ClassTypeSignature> addProperty(std::string key, std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature);
    std::shared_ptr<ClassTypeSignature> addMethod(std::string key, std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature);
    std::shared_ptr<ClassTypeSignature> addImplementsInterface(std::string key, std::shared_ptr<TypeSignature> interfaceTypeSignature);
    void setClassScopeParameter(std::shared_ptr<ParameterListItemTypeSignature> classScopeParameter);
    bool isClassScopeParameterNecessary();
    bool satisfiesImplementInterfaces();
    std::string getPreConstructorName();
    std::optional<std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>>> findConstructorForArguments(std::vector<std::shared_ptr<TypeSignature>>* argumentTypeSignatures);
    std::string addClassNameToKey(std::string key);
    std::string stripClassNameFromKey(std::string key);
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool hasCircularReferenceWith(std::shared_ptr<ClassTypeSignature> other);
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void copyFrom(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_H
