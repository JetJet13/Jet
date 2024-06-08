//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature-strategy.h"
#include "../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"

void EnumTypeSignatureStrategy::assign(ASTEnumDeclarationNode* enumDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    if (enumDeclaration->getValues()->getParameters().empty()) {
        enumDeclaration->setTypeSignature(new EnumTypeSignature(new DefaultEnumKeyValueTypeSignature()));
        return;
    }

    auto enumTypeSignature = new EnumTypeSignature();
    for (auto enumKeyValue : enumDeclaration->getValues()->getParameters()) {
        strategyMap->assignTypeSignatureFor(enumKeyValue);
        if (enumTypeSignature->getType()->typeTargetIs(LITERAL_TYPE_SOURCE)) {
            enumTypeSignature->setType(enumKeyValue->getTypeSignature());
        }
        enumTypeSignature->addKey(enumKeyValue->getKey()->getId());
    }

    enumDeclaration->setTypeSignature(enumTypeSignature);
}