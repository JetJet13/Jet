//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../type-signature/function-type-signature/function-type-signature.h"

TypeSignature* FunctionInvocationExpressionTypeSignatureStrategy::create(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto functionTypeSignature = typeSignatureLookupTable->find(functionInvocationExpression->getName()->getId());
    if (!functionTypeSignature->hasTypeSource(FUNCTION_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    return ((FunctionTypeSignature*)functionTypeSignature)->getReturnType();
}