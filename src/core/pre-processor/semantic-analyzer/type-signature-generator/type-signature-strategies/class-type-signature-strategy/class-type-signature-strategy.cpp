//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/class-type-signature.h"

ClassTypeSignature* ClassTypeSignatureStrategy::create(ASTClassDeclarationNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = new ClassTypeSignature();
    this->createPropertyTypeSignatures(node, classTypeSignature, strategyMap);
    this->createConstructorTypeSignatures(node, classTypeSignature, strategyMap);
    this->createMethodTypeSignatures(node, classTypeSignature, strategyMap);
    return classTypeSignature;
}

void ClassTypeSignatureStrategy::createConstructorTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto constructor : *node->getBlock()->getConstructors()) {
        classTypeSignature->addConstructor(
            constructor->getId(),
            strategyMap->getTypeSignatureForClassConstructor(constructor)
        );
    }
}

void ClassTypeSignatureStrategy::createPropertyTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        classTypeSignature->addProperty(
                property->getId(),
                strategyMap->getTypeSignatureForClassProperty(property)
        );
    }
}

void ClassTypeSignatureStrategy::createMethodTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto method : *node->getBlock()->getMethods()) {
        classTypeSignature->addMethod(
                method->getId(),
                strategyMap->getTypeSignatureForClassMethod(method)
        );
    }
}