//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"


void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto functionTypeSignature = typeSignatureLookupTable->find(
            functionInvocationExpression->getFunction()->getId()
    );

    if (functionTypeSignature->isInvocable()) {
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature(
            (InvocableTypeSignature*)functionTypeSignature)
        );
    } else {
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
    }
}