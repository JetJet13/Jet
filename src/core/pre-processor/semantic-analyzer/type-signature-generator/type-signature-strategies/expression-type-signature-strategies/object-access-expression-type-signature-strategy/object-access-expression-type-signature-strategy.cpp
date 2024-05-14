//
// Created by Johny Georges on 2024-05-11.
//

#include "object-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../../../../type-signature/enum-type-signature/enum-type-signature.h"

TypeSignature* ObjectAccessExpressionTypeSignatureStrategy::create(ASTObjectAccessExpressionNode* objectAccessExpression, TokenTable* tokenTable, TypeSignatureStrategyProvider* strategyMap) {
    auto sourceTypeSignature = strategyMap->getTypeSignatureForExpression(objectAccessExpression->getSource()->getSource());
    if (sourceTypeSignature->is(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)sourceTypeSignature;
        auto key = tokenTable->getIdentifier(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getIdentifier()->getToken()->getValueId().value());
        return structSource->getTypeSignatureForKey(key.value());

    } else if (sourceTypeSignature->is(ENUM_TYPE_SOURCE)) {
        auto enumSource = (EnumTypeSignature*)sourceTypeSignature;
        auto key = tokenTable->getIdentifier(objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getIdentifier()->getToken()->getValueId().value());
        if (enumSource->hasKey(key.value())) {
            return enumSource->getType();
        }
    }
    return new InvalidTypeSignature();
}