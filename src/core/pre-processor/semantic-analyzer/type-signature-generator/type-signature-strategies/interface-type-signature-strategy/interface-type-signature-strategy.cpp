//
// Created by Johny Georges on 2025-06-28.
//

#include "interface-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void InterfaceTypeSignatureStrategy::assign(ASTInterfaceTypeDeclarationNode* interfaceTypeDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto property : interfaceTypeDeclaration->getProperties()->getProperties()) {
        strategyMap->assignTypeSignatureFor(property, scope);
        auto propertyTypeSignature = property->getTypeSignature()->getTypeSignature()->convertToVariableTypeSignature();
        auto name = property->getTypeSignature()->getName();
        if (propertyTypeSignature->isInvocable()) {
            auto invocableTypeSignature = (InvocableTypeSignature*)propertyTypeSignature;
            name = FunctionIdGenerator::generateFor(name, invocableTypeSignature);
        }
        interfaceTypeDeclaration->getTypeSignature()->addProperty(
            name,
            propertyTypeSignature
        );
    }

}