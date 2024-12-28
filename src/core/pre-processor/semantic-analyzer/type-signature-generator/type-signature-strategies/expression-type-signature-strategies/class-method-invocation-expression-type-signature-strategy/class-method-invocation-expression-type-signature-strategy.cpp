//
// Created by Johny Georges on 2024-05-07.
//

#include "class-method-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ClassMethodInvocationExpressionTypeSignatureStrategy::assign(ASTClassMethodInvocationExpressionNode* classMethodInvocationExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = (ClassTypeSignature*)scope->find(classMethodInvocationExpression->getClassAccess()->getThis()->getId());
    auto classMethodTypeSignature = classTypeSignature->getMethods()->find(classMethodInvocationExpression->getName()->getId());
    if (!classMethodTypeSignature) {
        classMethodInvocationExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    classMethodInvocationExpression->getName()->setTypeSignature(classMethodTypeSignature.value());
    for (auto argument : *classMethodInvocationExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), scope);
    }
    auto classMethodReturnType = (classMethodTypeSignature.value())->getReturnType();
    classMethodInvocationExpression->setTypeSignature(classMethodReturnType);
}