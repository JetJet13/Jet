//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature-strategy.h"
#include "../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"

void EnumTypeSignatureStrategy::assign(std::shared_ptr<ASTEnumDeclarationNode> enumDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    if (enumDeclaration->getValues()->getParameters().empty()) {
        enumDeclaration->setTypeSignature(std::make_shared<EnumTypeSignature>(std::make_shared<DefaultEnumKeyValueTypeSignature>()));
        enumDeclaration->getTypeSignature()->setId(enumDeclaration->getId());
        scope->insertGlobal(
                enumDeclaration->getId(),
                enumDeclaration->getTypeSignature()
        );
        return;
    }

    auto enumTypeSignature = std::make_shared<EnumTypeSignature>();
    enumTypeSignature->setId(enumDeclaration->getId());
    for (auto enumKeyValue : enumDeclaration->getValues()->getParameters()) {
        strategyMap->assignTypeSignatureFor(enumKeyValue, context);
        if (enumTypeSignature->getType()->typeTargetIs(LITERAL_TYPE_SOURCE)) {
            enumTypeSignature->setType(enumKeyValue->getLiteralTypeSignature());
        }
        enumTypeSignature->addKey(enumKeyValue->getKey()->getId());
    }

    enumDeclaration->setTypeSignature(enumTypeSignature);
    scope->insertGlobal(
            enumDeclaration->getId(),
            enumDeclaration->getTypeSignature()
    );
}