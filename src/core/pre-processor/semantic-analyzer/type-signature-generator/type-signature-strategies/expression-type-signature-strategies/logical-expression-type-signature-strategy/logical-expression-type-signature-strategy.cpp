//
// Created by Johny Georges on 2024-05-07.
//

#include "logical-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"


void LogicalExpressionTypeSignatureStrategy::assign(ASTLogicalExpressionNode* logicalExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(logicalExpression->getLeftNode(), context, scope);
    strategyMap->assignTypeSignatureFor(logicalExpression->getRightNode(), context, scope);
    if (logicalExpression->getLeftNode()->getTypeSignature()->typeTargetIs(INVALID_TYPE_SOURCE) ||
        logicalExpression->getRightNode()->getTypeSignature()->typeTargetIs(INVALID_TYPE_SOURCE)) {
        logicalExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }
    logicalExpression->setTypeSignature(new BoolLiteralTypeSignature());
}