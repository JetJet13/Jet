//
// Created by Johny Georges on 2024-05-07.
//

#include "array-access-expression-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../type-signature/array-type-signature/array-type-signature.h"

TypeSignature* ArrayAccessExpressionTypeSignatureStrategy::create(ASTArrayAccessExpressionNode* arrayAccessExpression, ExpressionTypeSignatureStrategyProvider* strategyMap) {
    auto sourceTypeSignature = strategyMap->getTypeSignatureForExpression(arrayAccessExpression->getSource());
    if (!sourceTypeSignature->hasTypeSource(ARRAY_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    return ((ArrayTypeSignature*)sourceTypeSignature)->getElementType();
}