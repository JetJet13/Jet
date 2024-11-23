//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"


void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto functionTypeSignature = typeSignatureLookupTable->find(
            functionInvocationExpression->getFunction()->getId()
    );
    for (auto argument : *functionInvocationExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), typeSignatureLookupTable);
    }
    if (functionTypeSignature->isInvocable()) {
        functionInvocationExpression->getFunction()->setTypeSignature(functionTypeSignature);
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature(
            (InvocableTypeSignature*)functionTypeSignature)
        );
    } else {
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
    }
}