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
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"
#include "../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../type-signature/class-type-signature/class-type-signature.h"

class ClassTypeSignatureStrategy {
private:
    void assignConstructorTypeSignatures(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignPropertyTypeSignatures(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignMethodTypeSignatures(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignConstructorBlocksTypeSignature(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignMethodBlocksTypeSignature(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
public:
    void assign(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assignPostInitial(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H
