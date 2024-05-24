//
// Created by Johny Georges on 2024-05-13.
//

#include "class-constructor-type-signature-strategy.h"

void ClassConstructorTypeSignatureStrategy::assign(ASTClassConstructorDeclarationNode* classConstructorDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classConstructorDeclaration->getParameters(), scope);
    classConstructorDeclaration->setTypeSignature(new ClassConstructorTypeSignature(
        classConstructorDeclaration->getParameters()->getTypeSignature()
    ));
}