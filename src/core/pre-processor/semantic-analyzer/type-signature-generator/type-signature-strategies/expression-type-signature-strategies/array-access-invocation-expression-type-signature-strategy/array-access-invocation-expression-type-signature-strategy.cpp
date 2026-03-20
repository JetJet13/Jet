//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-type-signature-strategy.h"

void ArrayAccessInvocationExpressionTypeSignatureStrategy::assign(ASTArrayAccessInvocationExpressionNode* arrayAccessInvocationExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessInvocationExpression->getArrayAccess(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessInvocationExpression->getArguments(), context, scope);
    auto invocableTypeSignature = (InvocableTypeSignature*)arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature();
    arrayAccessInvocationExpression->setTypeSignature(invocableTypeSignature->getReturnType());
}
