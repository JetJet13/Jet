//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature-strategy.h"
#include "../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"

EnumTypeSignature* EnumTypeSignatureStrategy::create(ASTEnumDeclarationNode* enumDeclaration, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    if (enumDeclaration->getValues()->getParameters().empty()) {
        return new EnumTypeSignature(new DefaultEnumKeyValueTypeSignature());
    }

    auto firstEnumValueTypeSignature = strategyMap->getTypeSignatureForEnumKeyValue(enumDeclaration->getValues()->getParameters()[0]);
    auto enumTypeSignature = new EnumTypeSignature(firstEnumValueTypeSignature);
    for (auto enumKeyValue : enumDeclaration->getValues()->getParameters()) {
        auto key = tokenTable->getIdentifier(enumKeyValue->getKey()->getLexeme()->getToken()->getValueId().value());
        enumTypeSignature->addKey(key.value());
    }

    return enumTypeSignature;
}