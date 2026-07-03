//
// Created by Johny Georges on 2024-05-07.
//

#include "class-method-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ClassMethodInvocationExpressionTypeSignatureStrategy::assign(ASTClassMethodInvocationExpressionNode* classMethodInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto classTypeSignature = (ClassTypeSignature*)scope->find(classMethodInvocationExpression->getClassAccess()->getThis()->getId());
    auto classMethodTypeSignature = classTypeSignature->getInstanceMethods()->find(classMethodInvocationExpression->getName()->getId());
    if (!classMethodTypeSignature) {
        classMethodInvocationExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    classMethodInvocationExpression->getName()->setTypeSignature(classMethodTypeSignature.value());
    for (auto argument : *classMethodInvocationExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), context, scope);
    }
    auto classMethodReturnType = (classMethodTypeSignature.value())->getReturnType();
    classMethodInvocationExpression->setTypeSignature(classMethodReturnType);
}