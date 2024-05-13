//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"

TypeSignature* ClassPropertyTypeSignatureStrategy::create(ASTClassPropertyDeclarationNode* classPropertyDeclaration, TypeSignatureStrategyProvider* strategyMap) {;
    TypeSignature* classPropertyType = new UnknownTypeSignature();
    if (classPropertyDeclaration->getType()) {
        classPropertyType = strategyMap->getTypeSignatureFor(classPropertyDeclaration->getType().value());
    } else if (classPropertyDeclaration->getInitializer()) {
        classPropertyType = strategyMap->getTypeSignatureFor(classPropertyDeclaration->getInitializer().value());
    }

    return new ClassPropertyTypeSignature(
        (AccessModifierTypeSignature*)strategyMap->getTypeSignatureFor(classPropertyDeclaration->getAccessModifier()),
        classPropertyType,
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    );
}