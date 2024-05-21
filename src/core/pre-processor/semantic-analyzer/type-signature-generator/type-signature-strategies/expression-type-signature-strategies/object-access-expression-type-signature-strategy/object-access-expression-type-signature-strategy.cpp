//
// Created by Johny Georges on 2024-05-11.
//

#include "object-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../../../../type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../../../type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"

TypeSignature* ObjectAccessExpressionTypeSignatureStrategy::create(ASTObjectAccessExpressionNode* objectAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto sourceTypeSignature = strategyMap->getTypeSignatureForExpression(objectAccessExpression->getSource()->getSource(), scope);
    if (sourceTypeSignature->is(STRUCT_TYPE_SOURCE)) {
        auto structSource = (StructTypeSignature*)sourceTypeSignature;
        return structSource->getTypeSignatureForKey(
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        );
    } else if (sourceTypeSignature->is(ENUM_TYPE_SOURCE)) {
        auto enumSource = (EnumTypeSignature*)sourceTypeSignature;
        return new EnumAccessTypeSignature(
            enumSource,
            objectAccessExpression->getTarget()->getTarget()->getIdentifierNode()->getId()
        );
    }
    return new InvalidTypeSignature();
}