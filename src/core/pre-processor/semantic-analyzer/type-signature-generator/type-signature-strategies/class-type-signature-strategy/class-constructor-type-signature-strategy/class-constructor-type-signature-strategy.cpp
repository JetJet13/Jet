//
// Created by Johny Georges on 2024-05-13.
//

#include "class-constructor-type-signature-strategy.h"

void ClassConstructorTypeSignatureStrategy::assign(std::shared_ptr<ASTClassConstructorDeclarationNode> classConstructorDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classConstructorDeclaration->getParameters(), context, scope);
    classConstructorDeclaration->setTypeSignature(std::make_shared<ClassConstructorTypeSignature>(
        classConstructorDeclaration->getParameters()->getParameterListTypeSignature()
    ));
}