//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../../../shared/utils/logger/logger.h"

void ClassTypeSignatureStrategy::assign(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = new ClassTypeSignature();
    classTypeSignature->setId(node->getId());
    node->setTypeSignature(classTypeSignature);
    scope->insertGlobal(node->getId(), node->getTypeSignature());

    auto classScope = TypeSignatureLookupTable();
    classScope.inheritGlobalScope(scope);

    this->assignPropertyTypeSignatures(node, &classScope, classTypeSignature, strategyMap);
    classTypeSignature->setClassScopeParameter(strategyMap->generateClassScopeParameter(classTypeSignature));

    this->assignConstructorTypeSignatures(node, &classScope, classTypeSignature, strategyMap);
    this->assignMethodTypeSignatures(node, &classScope, classTypeSignature, strategyMap);
    this->assignConstructorBlocksTypeSignature(node, &classScope, classTypeSignature, strategyMap);
    this->assignMethodBlocksTypeSignature(node, &classScope, classTypeSignature, strategyMap);
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

void ClassTypeSignatureStrategy::assignConstructorBlocksTypeSignature(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        auto constructorScope = TypeSignatureLookupTable();
        constructorScope.inheritGlobalScope(scope);
        constructorScope.insert(classTypeSignature->getClassScopeParameter()->getName(), classTypeSignature->getClassScopeParameter()->getTypeSignature());
        strategyMap->assignTypeSignatureFor(constructor->getParameters(), &constructorScope);
        for (auto parameter : constructor->getParameters()->getParameters()) {
            constructorScope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
        }
        strategyMap->assignTypeSignatureFor(constructor->getBlock(), &constructorScope);
    }
}

void ClassTypeSignatureStrategy::assignMethodBlocksTypeSignature(ASTClassDeclarationNode* node, TypeSignatureLookupTable* scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        auto methodScope = TypeSignatureLookupTable();
        methodScope.inheritGlobalScope(scope);
        methodScope.insert(classTypeSignature->getClassScopeParameter()->getName(), classTypeSignature->getClassScopeParameter()->getTypeSignature());
        strategyMap->assignTypeSignatureFor(method->getParameters(), &methodScope);
        for (auto parameter : method->getParameters()->getParameters()) {
            methodScope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
        }
        strategyMap->assignTypeSignatureFor(method->getBlock(), &methodScope);
        Logger::log("method scope");
        methodScope.dump();
    }
}
