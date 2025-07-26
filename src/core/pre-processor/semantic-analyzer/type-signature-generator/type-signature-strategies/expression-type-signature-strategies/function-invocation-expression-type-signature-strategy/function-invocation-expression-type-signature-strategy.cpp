//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"


void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignature = typeSignatureLookupTable->find(
            functionInvocationExpression->getFunction()->getId()
    );
    for (auto argument : *functionInvocationExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), typeSignatureLookupTable);
    }
    if (typeSignature->isInvocable()) {
        functionInvocationExpression->getFunction()->setTypeSignature(typeSignature);
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature(
            (InvocableTypeSignature*)typeSignature)
        );
    } else {
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
    }
}