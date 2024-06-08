//
// Created by Johny Georges on 2024-05-07.
//

#include "class-method-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void ClassMethodInvocationExpressionTypeSignatureStrategy::assign(ASTClassMethodInvocationExpressionNode* classMethodInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto classMethodTypeSignature = typeSignatureLookupTable->find(classMethodInvocationExpression->getName()->getId());
    if (!classMethodTypeSignature->typeTargetIs(CLASS_METHOD_TYPE_SOURCE)) {
        classMethodInvocationExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    classMethodInvocationExpression->getName()->setTypeSignature((ClassMethodTypeSignature*)classMethodTypeSignature);
    for (auto argument : *classMethodInvocationExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument());
    }
    auto classMethodReturnType = ((ClassMethodTypeSignature*)classMethodTypeSignature)->getReturnType();
    classMethodInvocationExpression->setTypeSignature(classMethodReturnType);
}