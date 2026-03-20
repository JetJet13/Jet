//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ClassPropertyTypeSignatureStrategy::assign(ASTClassPropertyDeclarationNode* classPropertyDeclaration, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {;
    TypeSignature* classPropertyType = new UnknownTypeSignature();
    if (classPropertyDeclaration->getInitializer()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getInitializer().value(), context, scope);
        classPropertyType = classPropertyDeclaration->getInitializer().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else if (classPropertyDeclaration->getType()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getType().value(), context, scope);
        classPropertyType = classPropertyDeclaration->getType().value()->getTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getAccessModifier(), context);
    classPropertyDeclaration->setTypeSignature(new ClassPropertyTypeSignature(
        classPropertyDeclaration->getAccessModifier()->getTypeSignature(),
        classPropertyType->convertToVariableTypeSignature(),
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    ));
    classPropertyType->setKeyId(classPropertyDeclaration->getNormalizedPropertyName());
    classPropertyDeclaration->getTypeSignature()->setKeyId(classPropertyDeclaration->getNormalizedPropertyName());
}