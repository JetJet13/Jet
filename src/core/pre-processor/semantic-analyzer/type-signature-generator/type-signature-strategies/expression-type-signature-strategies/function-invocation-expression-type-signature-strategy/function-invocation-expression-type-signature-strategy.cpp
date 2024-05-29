//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/function-type-signature/function-type-signature.h"
#include "../../../../../../type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"

void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto functionTypeSignature = typeSignatureLookupTable->find(
            functionInvocationExpression->getName()->getId()
    );

    if (!functionTypeSignature->is(FUNCTION_TYPE_SOURCE)) {
        functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
        return;
    }
    functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature((FunctionTypeSignature*)functionTypeSignature));
}