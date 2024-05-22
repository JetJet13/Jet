//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"

void ClassTypeSignatureStrategy::assign(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = new ClassTypeSignature();
    this->assignPropertyTypeSignatures(node, scope, classTypeSignature, strategyMap);
    this->assignConstructorTypeSignatures(node, scope, classTypeSignature, strategyMap);
    this->assignMethodTypeSignatures(node, scope, classTypeSignature, strategyMap);
    node->setTypeSignature(classTypeSignature);
}

void ClassTypeSignatureStrategy::assignConstructorTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        strategyMap->assignTypeSignatureForClassConstructor(constructor, scope);
        for (int i = 0; i < constructor->getParameters()->numParameters(); ++i) {
            auto parameter = constructor->getParameters()->getParameters().at(i);
            if (parameter->getType()->getType()->getId() == node->getId()) {
                constructor
                ->getTypeSignature()
                ->getParameterList()
                ->getParameters()
                ->at(i)
                ->setType(new ClassInstanceTypeSignature(classTypeSignature));
            }
        }
        classTypeSignature->addConstructor(
            constructor->getId(),
            constructor->getTypeSignature()
        );
    }
}

void ClassTypeSignatureStrategy::assignPropertyTypeSignatures(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        strategyMap->assignTypeSignatureForClassProperty(property, scope);
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
        strategyMap->assignTypeSignatureForClassMethod(method, scope);
        for (int i = 0; i < method->getParameters()->numParameters(); ++i) {
            auto parameter = method->getParameters()->getParameters().at(i);
            if (parameter->getType()->getType()->getId() == node->getId()) {
                method
                ->getTypeSignature()
                ->getParameters()
                ->getParameters()
                ->at(i)
                ->setType(new ClassInstanceTypeSignature(classTypeSignature));
            }
        }
        if (method->getTypeSignature() &&
            method->getReturnType() &&
            method->getReturnType().value()->getType()->getId() == node->getId()) {
            method->getTypeSignature()->setReturnType(new ClassInstanceTypeSignature(classTypeSignature));
        }
        classTypeSignature->addMethod(
                method->getId(),
                method->getTypeSignature()
        );
    }
}