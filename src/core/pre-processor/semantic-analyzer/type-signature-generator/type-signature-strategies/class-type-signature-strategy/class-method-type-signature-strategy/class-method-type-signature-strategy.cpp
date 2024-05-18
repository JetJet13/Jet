//
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"

ClassMethodTypeSignature* ClassMethodTypeSignatureStrategy::create(ASTClassMethodDeclarationNode* classMethodDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<TypeSignature*> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        returnType = strategyMap->getTypeSignatureForType(classMethodDeclaration->getReturnType().value(), scope);
    }

    return new ClassMethodTypeSignature(
            strategyMap->getTypeSignatureForAccessModifier(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()),
            strategyMap->getTypeSignatureForParameterList(classMethodDeclaration->getParameters(), scope),
            classMethodDeclaration->getClassMethodDefinition()->isStatic(),
            returnType
    );
}