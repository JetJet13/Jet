
//
// Created by Johny Georges on 2024-05-07.
//

#include "array-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void ArrayAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessExpression->getSource(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessExpression->getIndex()->getIndex(), context, scope);

    if (arrayAccessExpression->getSource()->getTypeSignature()->typeTargetIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = std::dynamic_pointer_cast<RefTypeSignature>(arrayAccessExpression->getSource()->getTypeSignature()->getTargetTypeSignature());
        if (refTypeSignature->getUnderlyingType()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
            auto arrayTypeSignature = std::dynamic_pointer_cast<ArrayTypeSignature>(refTypeSignature->getUnderlyingType()->getTargetTypeSignature());
            arrayAccessExpression->setTypeSignature(arrayTypeSignature->getElementType());
            return;
        }
        arrayAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
        return;
    }

    if (arrayAccessExpression->getSource()->getTypeSignature()->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        arrayAccessExpression->setTypeSignature((std::dynamic_pointer_cast<ArrayTypeSignature>(arrayAccessExpression->getSource()->getTypeSignature()->getTargetTypeSignature())->getElementType()));
        return;
    }

    arrayAccessExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}