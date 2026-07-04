//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-type-signature-strategy.h"

void ArrayAccessInvocationExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> arrayAccessInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(arrayAccessInvocationExpression->getArrayAccess(), context, scope);
    strategyMap->assignTypeSignatureFor(arrayAccessInvocationExpression->getArguments(), context, scope);
    auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(arrayAccessInvocationExpression->getArrayAccess()->getTypeSignature());
    arrayAccessInvocationExpression->setTypeSignature(invocableTypeSignature->getReturnType());
}
