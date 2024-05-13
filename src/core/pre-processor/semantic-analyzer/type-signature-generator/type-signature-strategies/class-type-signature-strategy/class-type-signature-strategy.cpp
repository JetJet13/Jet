//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/class-type-signature.h"

TypeSignature* ClassTypeSignatureStrategy::create(ASTClassDeclarationNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = new ClassTypeSignature();
    this->createPropertyTypeSignatures(node, classTypeSignature, strategyMap);
    this->createConstructorTypeSignatures(node, classTypeSignature, strategyMap);
    this->createMethodTypeSignatures(node, classTypeSignature, strategyMap);
    return classTypeSignature;
}

void ClassTypeSignatureStrategy::createConstructorTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        auto typeSignature = strategyMap->getTypeSignatureFor(property);
        if (typeSignature->is(CLASS_CONSTRUCTOR_TYPE_SOURCE)) {
            classTypeSignature->addConstructor(
                    property->getId(),
                    (ClassConstructorTypeSignature*)strategyMap->getTypeSignatureFor(property)
            );
        }
    }
}

void ClassTypeSignatureStrategy::createPropertyTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        auto typeSignature = strategyMap->getTypeSignatureFor(property);
        if (typeSignature->is(CLASS_PROPERTY_TYPE_SOURCE)) {
            classTypeSignature->addProperty(
                    property->getId(),
                    (ClassPropertyTypeSignature*)strategyMap->getTypeSignatureFor(property)
            );
        }
    }
}

void ClassTypeSignatureStrategy::createMethodTypeSignatures(ASTClassDeclarationNode* node, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : *node->getBlock()->getProperties()) {
        auto typeSignature = strategyMap->getTypeSignatureFor(property);
        if (typeSignature->is(CLASS_METHOD_TYPE_SOURCE)) {
            classTypeSignature->addMethod(
                    property->getId(),
                    (ClassMethodTypeSignature*)strategyMap->getTypeSignatureFor(property)
            );
        }
    }
}