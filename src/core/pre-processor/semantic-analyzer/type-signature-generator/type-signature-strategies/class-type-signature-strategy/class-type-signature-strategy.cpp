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

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ClassTypeSignatureStrategy::assign(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = node->getClassTypeSignature();
    auto classScope = std::make_shared<TypeSignatureLookupTable>();
    classScope->inheritGlobalScope(scope);
    this->assignPropertyTypeSignatures(node, context, classScope, classTypeSignature, strategyMap);
    classTypeSignature->setClassScopeParameter(strategyMap->generateClassScopeParameter(classTypeSignature));

    this->assignConstructorBlocksTypeSignature(node, context, classScope, classTypeSignature, strategyMap);
    this->assignMethodBlocksTypeSignature(node, context, classScope, classTypeSignature, strategyMap);

    if (node->getImplementsInterfaceList()->has_value()) {
        for (auto interfaceName : node->getImplementsInterfaceList()->value()->getInterfaceNames()) {
            classTypeSignature->addImplementsInterface(interfaceName->getId(), scope->find(interfaceName->getId()));
        }
    }
}

void ClassTypeSignatureStrategy::assignPostInitial(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = node->getClassTypeSignature();
    auto classScope = std::make_shared<TypeSignatureLookupTable>();
    classScope->inheritGlobalScope(scope);

    this->assignMethodTypeSignatures(node, context, classScope, classTypeSignature, strategyMap);
    this->assignConstructorTypeSignatures(node, context, classScope, classTypeSignature, strategyMap);
}

void ClassTypeSignatureStrategy::assignConstructorTypeSignatures(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatureContext = std::make_shared<TypeSignatureContext>();
    for (auto constructor : *node->getBlock()->getConstructors()) {
        strategyMap->assignTypeSignatureFor(constructor, typeSignatureContext, scope);
        classTypeSignature->addConstructor(
            constructor->getId(),
            constructor->getConstructorTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignPropertyTypeSignatures(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, context, scope);
        if (property->getPropertyInit()->getType() &&
            property->getPropertyInit()->getType().value()->getType()->getId() == node->getId()) {
            property->getPropertyTypeSignature()->setType(classTypeSignature->convertToVariableTypeSignature());
        }

        if (property->getInitializer() && property->getInitializer().value()->is(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
            auto newClassInstanceExpression = std::dynamic_pointer_cast<ASTNewClassInstanceExpressionNode>(property->getInitializer().value());
            if (newClassInstanceExpression->getClassName() == node->getId()) {
                property->getPropertyTypeSignature()->setType(classTypeSignature->convertToVariableTypeSignature());
            }
        }

        classTypeSignature->addProperty(
                property->getId(),
                property->getPropertyTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignMethodTypeSignatures(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        strategyMap->assignTypeSignatureFor(method, context, scope);
        auto methodId = FunctionIdGenerator::generateFor(method);
        classTypeSignature->addMethod(
                methodId,
                method->getMethodTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignConstructorBlocksTypeSignature(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        auto constructorScope = std::make_shared<TypeSignatureLookupTable>();
        constructorScope->inheritGlobalScope(scope);
        constructorScope->insert(classTypeSignature->getClassScopeParameter()->getName(), classTypeSignature->getClassScopeParameter()->getTypeSignature());
        strategyMap->assignTypeSignatureFor(constructor->getParameters(), context, constructorScope);
        for (auto parameter : constructor->getParameters()->getParameters()) {
            constructorScope->insert(parameter->getParameterTypeSignature()->getName(), parameter->getParameterTypeSignature()->getTypeSignature());
        }
        strategyMap->assignTypeSignatureFor(constructor->getBlock(), context, constructorScope);
    }
}

void ClassTypeSignatureStrategy::assignMethodBlocksTypeSignature(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, std::shared_ptr<ClassTypeSignature> classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        auto methodScope = std::make_shared<TypeSignatureLookupTable>();
        methodScope->inheritGlobalScope(scope);
        methodScope->insert(classTypeSignature->getClassScopeParameter()->getName(), classTypeSignature->getClassScopeParameter()->getTypeSignature());
        strategyMap->assignTypeSignatureFor(method->getParameters(), context, methodScope);
        for (auto parameter : method->getParameters()->getParameters()) {
            methodScope->insert(parameter->getParameterTypeSignature()->getName(), parameter->getParameterTypeSignature()->getTypeSignature());
        }
        strategyMap->assignTypeSignatureFor(method->getBlock(), context, methodScope);
    }
}
