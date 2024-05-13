//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature-strategy.h"
#include "../../../../../type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"
#include "../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* EnumTypeSignatureStrategy::create(ASTEnumDeclarationNode* enumDeclaration, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    if (enumDeclaration->getValues()->getParameters().empty()) {
        return new EnumTypeSignature(new DefaultEnumKeyValueTypeSignature());
    }

    TypeSignature* lastEnumValueTypeSignature = strategyMap->getTypeSignatureFor(enumDeclaration->getValues()->getParameters()[0]);
    for (auto enumKeyValue : enumDeclaration->getValues()->getParameters()) {
        auto enumKeyValueTypeSignature = strategyMap->getTypeSignatureFor(enumKeyValue);
        if (!lastEnumValueTypeSignature->isEqualTo(enumKeyValueTypeSignature) || !enumKeyValueTypeSignature->isLiteral()) {
            return new InvalidTypeSignature();
        }
    }

    auto enumTypeSignature = new EnumTypeSignature((LiteralTypeSignature*)lastEnumValueTypeSignature);
    for (auto enumKeyValue : enumDeclaration->getValues()->getParameters()) {
        auto key = tokenTable->getIdentifier(enumKeyValue->getKey()->getLexeme()->getToken()->getValueId().value());
        enumTypeSignature->addKey(key.value());
    }

    return enumTypeSignature;
}