//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"

void ClassPropertyTypeSignatureStrategy::assign(ASTClassPropertyDeclarationNode* classPropertyDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {;
    classPropertyDeclaration->getPropertyInit();

    TypeSignature* classPropertyType = new UnknownTypeSignature();
    if (classPropertyDeclaration->getInitializer()) {
        strategyMap->assignTypeSignatureForExpression(classPropertyDeclaration->getInitializer().value(), scope);
        classPropertyType = classPropertyDeclaration->getInitializer().value()->getTypeSignature();
    }

    if (classPropertyDeclaration->getType()) {
        strategyMap->assignTypeSignatureForType(classPropertyDeclaration->getType().value(), scope);
        classPropertyType = classPropertyDeclaration->getType().value()->getTypeSignature();
    }


    strategyMap->assignTypeSignatureForAccessModifier(classPropertyDeclaration->getAccessModifier());
    classPropertyDeclaration->setTypeSignature(new ClassPropertyTypeSignature(
        classPropertyDeclaration->getAccessModifier()->getTypeSignature(),
        classPropertyType,
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    ));
}