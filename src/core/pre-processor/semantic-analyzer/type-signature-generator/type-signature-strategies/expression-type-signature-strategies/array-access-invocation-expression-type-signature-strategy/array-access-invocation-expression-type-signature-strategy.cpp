//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-type-signature-strategy.h"

void ArrayAccessInvocationExpressionTypeSignatureStrategy::assign(ASTArrayAccessInvocationExpressionNode* arrayAccessInvocationExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessInvocationExpression->getArrayAccess(), scope);
    strategyMap->assignTypeSignatureFor(arrayAccessInvocationExpression->getArguments(), scope);
    auto invocableTypeSignature = (InvocableTypeSignature*)arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature();
    arrayAccessInvocationExpression->setTypeSignature(invocableTypeSignature->getReturnType());
}
