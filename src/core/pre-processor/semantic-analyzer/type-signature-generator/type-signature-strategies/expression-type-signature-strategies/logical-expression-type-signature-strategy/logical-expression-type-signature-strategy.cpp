//
// Created by Johny Georges on 2024-05-07.
//

#include "logical-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"


TypeSignature* LogicalExpressionTypeSignatureStrategy::create(ASTLogicalExpressionNode* logicalExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto leftTypeSignature = strategyMap->getTypeSignatureForExpression(logicalExpression->getLeftNode(), scope);
    auto rightTypeSignature = strategyMap->getTypeSignatureForExpression(logicalExpression->getRightNode(), scope);
    if (leftTypeSignature->is(INVALID_TYPE_SOURCE) || rightTypeSignature->is(INVALID_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }
    return new BoolLiteralTypeSignature();
}