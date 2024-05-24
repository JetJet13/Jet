//
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"

void ClassMethodTypeSignatureStrategy::assign(ASTClassMethodDeclarationNode* classMethodDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<TypeSignature*> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        strategyMap->assignTypeSignatureFor(classMethodDeclaration->getReturnType().value(), scope);
        returnType = classMethodDeclaration->getReturnType().value()->getTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier());
    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getParameters(), scope);
    classMethodDeclaration->setTypeSignature(new ClassMethodTypeSignature(
            classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()->getTypeSignature(),
            classMethodDeclaration->getParameters()->getTypeSignature(),
            classMethodDeclaration->getClassMethodDefinition()->isStatic(),
            returnType
    ));
}