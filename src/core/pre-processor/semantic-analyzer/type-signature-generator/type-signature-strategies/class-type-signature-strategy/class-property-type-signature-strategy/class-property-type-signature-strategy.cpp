//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"

ClassPropertyTypeSignature* ClassPropertyTypeSignatureStrategy::create(ASTClassPropertyDeclarationNode* classPropertyDeclaration, TypeSignatureStrategyProvider* strategyMap) {;
    TypeSignature* classPropertyType = new UnknownTypeSignature();
    if (classPropertyDeclaration->getType()) {
        classPropertyType = strategyMap->getTypeSignatureForType(classPropertyDeclaration->getType().value());
    } else if (classPropertyDeclaration->getInitializer()) {
        classPropertyType = strategyMap->getTypeSignatureForExpression(classPropertyDeclaration->getInitializer().value());
    }

    return new ClassPropertyTypeSignature(
        strategyMap->getTypeSignatureForAccessModifier(classPropertyDeclaration->getAccessModifier()),
        classPropertyType,
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    );
}