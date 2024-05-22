//
// Created by Johny Georges on 2024-05-07.
//

#include "logical-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"


void LogicalExpressionTypeSignatureStrategy::assign(ASTLogicalExpressionNode* logicalExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(logicalExpression->getLeftNode(), scope);
    strategyMap->assignTypeSignatureForExpression(logicalExpression->getRightNode(), scope);
    if (logicalExpression->getLeftNode()->getTypeSignature()->is(INVALID_TYPE_SOURCE) ||
        logicalExpression->getRightNode()->getTypeSignature()->is(INVALID_TYPE_SOURCE)) {
        logicalExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }
    logicalExpression->setTypeSignature(new BoolLiteralTypeSignature());
}