//
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"


void ConcatExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTConcatExpressionNode> concatExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(concatExpression->getLeftNode(), context, scope);
    strategyMap->assignTypeSignatureFor(concatExpression->getRightNode(), context, scope);
    auto leftTypeSignature = concatExpression->getLeftNode()->getTypeSignature();
    auto rightTypeSignature = concatExpression->getRightNode()->getTypeSignature();

    if (leftTypeSignature->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(leftTypeSignature->getTargetTypeSignature());
        leftTypeSignature = sharedTypeSignature->getUnderlyingType();
    }

    if (rightTypeSignature->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(rightTypeSignature->getTargetTypeSignature());
        rightTypeSignature = sharedTypeSignature->getUnderlyingType();
    }


    if (leftTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE) && rightTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)) {
        concatExpression->setTypeSignature(leftTypeSignature->getTargetTypeSignature());
        return;
    }
    if (leftTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE) && rightTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)) {
        concatExpression->setTypeSignature(leftTypeSignature->getTargetTypeSignature());
        return;
    }
    concatExpression->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}