//
// Created by Johny Georges on 2024-05-13.
//

#include "class-constructor-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"

ClassConstructorTypeSignature* ClassConstructorTypeSignatureStrategy::create(ASTClassConstructorDeclarationNode* classConstructorDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    return new ClassConstructorTypeSignature(
        strategyMap->getTypeSignatureForParameterList(classConstructorDeclaration->getParameters())
    );
}