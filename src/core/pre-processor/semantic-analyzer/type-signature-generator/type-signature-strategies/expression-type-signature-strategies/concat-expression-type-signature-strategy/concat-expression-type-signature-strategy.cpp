//
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"


void ConcatExpressionTypeSignatureStrategy::assign(ASTConcatExpressionNode* concatExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(concatExpression->getLeftNode(), scope);
    strategyMap->assignTypeSignatureFor(concatExpression->getRightNode(), scope);
    auto leftTypeSignature = concatExpression->getLeftNode()->getTypeSignature();
    auto rightTypeSignature = concatExpression->getRightNode()->getTypeSignature();

    if (leftTypeSignature->typeTargetIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = (RefTypeSignature*)leftTypeSignature->getTargetTypeSignature();
        leftTypeSignature = refTypeSignature->getUnderlyingType();
    }

    if (rightTypeSignature->typeTargetIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = (RefTypeSignature*)rightTypeSignature->getTargetTypeSignature();
        rightTypeSignature = refTypeSignature->getUnderlyingType();
    }


    if (leftTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE) && rightTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)) {
        concatExpression->setTypeSignature(leftTypeSignature->getTargetTypeSignature());
        return;
    }
    if (leftTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE) && rightTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        concatExpression->setTypeSignature(leftTypeSignature->getTargetTypeSignature());
        return;
    }
    concatExpression->setTypeSignature(new InvalidTypeSignature());
}