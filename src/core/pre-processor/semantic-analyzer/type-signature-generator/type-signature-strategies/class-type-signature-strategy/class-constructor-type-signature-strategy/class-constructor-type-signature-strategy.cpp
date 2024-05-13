//
// Created by Johny Georges on 2024-05-13.
//

#include "class-constructor-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"

TypeSignature* ClassConstructorTypeSignatureStrategy::create(ASTClassConstructorDeclarationNode* classConstructorDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    return new ClassConstructorTypeSignature(
        (ParameterListTypeSignature*)strategyMap->getTypeSignatureFor(classConstructorDeclaration->getParameters())
    );
}