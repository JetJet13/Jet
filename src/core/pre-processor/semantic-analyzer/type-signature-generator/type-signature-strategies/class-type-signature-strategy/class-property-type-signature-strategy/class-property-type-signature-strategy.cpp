//
// Created by Johny Georges on 2024-05-13.
//

#include "class-property-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ClassPropertyTypeSignatureStrategy::assign(std::shared_ptr<ASTClassPropertyDeclarationNode> classPropertyDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {;
    std::shared_ptr<TypeSignature> classPropertyType = std::make_shared<UnknownTypeSignature>();
    if (classPropertyDeclaration->getInitializer()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getInitializer().value(), context, scope);
        classPropertyType = classPropertyDeclaration->getInitializer().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else if (classPropertyDeclaration->getType()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getType().value(), context, scope);
        classPropertyType = classPropertyDeclaration->getType().value()->getTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getAccessModifier(), context);
    classPropertyDeclaration->setTypeSignature(std::make_shared<ClassPropertyTypeSignature>(
        classPropertyDeclaration->getAccessModifier()->getAccessModifierTypeSignature(),
        classPropertyType->convertToVariableTypeSignature(),
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    ));
    classPropertyType->setKeyId(classPropertyDeclaration->getNormalizedPropertyName());
    classPropertyDeclaration->getTypeSignature()->setKeyId(classPropertyDeclaration->getNormalizedPropertyName());
}