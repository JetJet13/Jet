//
// Created by Johny Georges on 2024-05-07.
//

#include "logical-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"


TypeSignature* LogicalExpressionTypeSignatureStrategy::create(ASTLogicalExpressionNode* logicalExpression, TypeSignatureStrategyProvider* strategyMap) {
    auto leftTypeSignature = strategyMap->getTypeSignatureFor(logicalExpression->getLeftNode());
    auto rightTypeSignature = strategyMap->getTypeSignatureFor(logicalExpression->getRightNode());
    if (leftTypeSignature->is(INVALID_TYPE_SOURCE) || rightTypeSignature->is(INVALID_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }
    return new BoolLiteralTypeSignature();
}