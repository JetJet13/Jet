//
// Created by Johny Georges on 2024-05-07.
//

#include "logical-expression-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"


TypeSignature* LogicalExpressionTypeSignatureStrategy::create(ASTLogicalExpressionNode* logicalExpression, ExpressionTypeSignatureStrategyProvider* strategyMap) {
    auto leftTypeSignature = strategyMap->getTypeSignatureForExpression(logicalExpression->getLeftNode());
    auto rightTypeSignature = strategyMap->getTypeSignatureForExpression(logicalExpression->getRightNode());
    if (leftTypeSignature->hasTypeSource(INVALID_TYPE_SOURCE) || rightTypeSignature->hasTypeSource(INVALID_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }
    return new BoolLiteralTypeSignature();
}