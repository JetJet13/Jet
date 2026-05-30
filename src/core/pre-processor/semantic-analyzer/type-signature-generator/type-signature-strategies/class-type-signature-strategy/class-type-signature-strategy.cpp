//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"

void ClassTypeSignatureStrategy::assign(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = node->getTypeSignature();
    auto classScope = TypeSignatureLookupTable();
    classScope.inheritGlobalScope(scope);
    this->assignPropertyTypeSignatures(node, context, &classScope, classTypeSignature, strategyMap);
    classTypeSignature->setClassScopeParameter(strategyMap->generateClassScopeParameter(classTypeSignature));

    this->assignConstructorBlocksTypeSignature(node, context, &classScope, classTypeSignature, strategyMap);
    this->assignMethodBlocksTypeSignature(node, context, &classScope, classTypeSignature, strategyMap);

    if (node->getImplementsInterfaceList()->has_value()) {
        for (auto interfaceName : node->getImplementsInterfaceList()->value()->getInterfaceNames()) {
            classTypeSignature->addImplementsInterface(interfaceName->getId(), scope->find(interfaceName->getId()));
        }
    }
}

void ClassTypeSignatureStrategy::assignPostInitial(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = node->getTypeSignature();
    auto classScope = TypeSignatureLookupTable();
    classScope.inheritGlobalScope(scope);

    this->assignMethodTypeSignatures(node, context, &classScope, classTypeSignature, strategyMap);
    this->assignConstructorTypeSignatures(node, context, &classScope, classTypeSignature, strategyMap);
}

void ClassTypeSignatureStrategy::assignConstructorTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatureContext = new TypeSignatureContext();
    for (auto constructor : *node->getBlock()->getConstructors()) {
        strategyMap->assignTypeSignatureFor(constructor, typeSignatureContext, scope);
        classTypeSignature->addConstructor(
            constructor->getId(),
            constructor->getTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignPropertyTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, context, scope);
        if (property->getPropertyInit()->getType() &&
            property->getPropertyInit()->getType().value()->getType()->getId() == node->getId()) {
            property->getTypeSignature()->setType(classTypeSignature->convertToVariableTypeSignature());
        }

        if (property->getInitializer() && property->getInitializer().value()->is(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
            auto newClassInstanceExpression = (ASTNewClassInstanceExpressionNode*)property->getInitializer().value();
            if (newClassInstanceExpression->getClassName() == node->getId()) {
                property->getTypeSignature()->setType(classTypeSignature->convertToVariableTypeSignature());
            }
        }

        classTypeSignature->addProperty(
                property->getId(),
                property->getTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignMethodTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        strategyMap->assignTypeSignatureFor(method, context, scope);
        classTypeSignature->addMethod(
                method->getId(),
                method->getTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignConstructorBlocksTypeSignature(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        auto constructorScope = TypeSignatureLookupTable();
        constructorScope.inheritGlobalScope(scope);
        constructorScope.insert(classTypeSignature->getClassScopeParameter()->getName(), classTypeSignature->getClassScopeParameter()->getTypeSignature());
        strategyMap->assignTypeSignatureFor(constructor->getParameters(), context, &constructorScope);
        for (auto parameter : constructor->getParameters()->getParameters()) {
            constructorScope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
        }
        strategyMap->assignTypeSignatureFor(constructor->getBlock(), context, &constructorScope);
    }
}

void ClassTypeSignatureStrategy::assignMethodBlocksTypeSignature(ASTClassDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        auto methodScope = TypeSignatureLookupTable();
        methodScope.inheritGlobalScope(scope);
        methodScope.insert(classTypeSignature->getClassScopeParameter()->getName(), classTypeSignature->getClassScopeParameter()->getTypeSignature());
        strategyMap->assignTypeSignatureFor(method->getParameters(), context, &methodScope);
        for (auto parameter : method->getParameters()->getParameters()) {
            methodScope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
        }
        strategyMap->assignTypeSignatureFor(method->getBlock(), context, &methodScope);
    }
}
