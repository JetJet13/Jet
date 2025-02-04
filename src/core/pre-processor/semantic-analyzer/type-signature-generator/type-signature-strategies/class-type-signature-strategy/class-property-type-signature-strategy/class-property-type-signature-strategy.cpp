//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ClassPropertyTypeSignatureStrategy::assign(ASTClassPropertyDeclarationNode* classPropertyDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {;
    TypeSignature* classPropertyType = new UnknownTypeSignature();
    if (classPropertyDeclaration->getInitializer()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getInitializer().value(), scope);
        classPropertyType = classPropertyDeclaration->getInitializer().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else if (classPropertyDeclaration->getType()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getType().value(), scope);
        classPropertyType = classPropertyDeclaration->getType().value()->getTypeSignature();
    }


    strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getAccessModifier());
    classPropertyDeclaration->setTypeSignature(new ClassPropertyTypeSignature(
        classPropertyDeclaration->getAccessModifier()->getTypeSignature(),
        classPropertyType,
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    ));
}