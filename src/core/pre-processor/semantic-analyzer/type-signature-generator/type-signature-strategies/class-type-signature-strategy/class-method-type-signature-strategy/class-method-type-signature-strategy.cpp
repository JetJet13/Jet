//
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"
#include "../../../../../../type-signature/access-modifier-type-signature/access-modifier-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"

TypeSignature* ClassMethodTypeSignatureStrategy::create(ASTClassMethodDeclarationNode* classMethodDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<TypeSignature*> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        returnType = strategyMap->getTypeSignatureFor(classMethodDeclaration->getReturnType().value());
    }

    return new ClassMethodTypeSignature(
            (AccessModifierTypeSignature*)strategyMap->getTypeSignatureFor(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()),
            (ParameterListTypeSignature*)strategyMap->getTypeSignatureFor(classMethodDeclaration->getParameters()),
            classMethodDeclaration->getClassMethodDefinition()->isStatic(),
            returnType
    );
}