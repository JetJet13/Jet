//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"


ClassPropertyTypeSignature* ClassPropertyTypeSignatureStrategy::create(ASTClassPropertyDeclarationNode* classPropertyDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {;
    TypeSignature* classPropertyType = new UnknownTypeSignature();
    if (classPropertyDeclaration->getType()) {
        classPropertyType = strategyMap->getTypeSignatureForType(classPropertyDeclaration->getType().value(), scope);
    } else if (classPropertyDeclaration->getInitializer()) {
        classPropertyType = strategyMap->getTypeSignatureForExpression(classPropertyDeclaration->getInitializer().value(), scope);
    }

    return new ClassPropertyTypeSignature(
        strategyMap->getTypeSignatureForAccessModifier(classPropertyDeclaration->getAccessModifier()),
        classPropertyType,
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    );
}