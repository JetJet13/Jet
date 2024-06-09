//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"

void ClassTypeSignatureStrategy::assign(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = new ClassTypeSignature();
    auto classScope = TypeSignatureLookupTable(scope);
    this->assignPropertyTypeSignatures(node, &classScope, classTypeSignature, strategyMap);
    this->assignConstructorTypeSignatures(node, &classScope, classTypeSignature, strategyMap);
    this->assignMethodTypeSignatures(node, &classScope, classTypeSignature, strategyMap);
    node->setTypeSignature(classTypeSignature);
    scope->insert(node->getId(), node->getTypeSignature());
}

void ClassTypeSignatureStrategy::assignConstructorTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        strategyMap->assignTypeSignatureFor(constructor, scope);
        classTypeSignature->addConstructor(
            constructor->getId(),
            constructor->getTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignPropertyTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, scope);
        if (property->getPropertyInit()->getType() &&
            property->getPropertyInit()->getType().value()->getType()->getId() == node->getId()) {
            property->getTypeSignature()->setType(new ClassInstanceTypeSignature(classTypeSignature));
        }

        if (property->getInitializer() && property->getInitializer().value()->is(AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
            auto newClassInstanceExpression = (ASTNewClassInstanceExpressionNode*)property->getInitializer().value();
            if (newClassInstanceExpression->getClassName()->getId() == node->getId()) {
                property->getTypeSignature()->setType(new ClassInstanceTypeSignature(classTypeSignature));
            }
        }

        classTypeSignature->addProperty(
                property->getId(),
                property->getTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignMethodTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        strategyMap->assignTypeSignatureFor(method, scope);
        classTypeSignature->addMethod(
                method->getId(),
                method->getTypeSignature()
        );
    }
}