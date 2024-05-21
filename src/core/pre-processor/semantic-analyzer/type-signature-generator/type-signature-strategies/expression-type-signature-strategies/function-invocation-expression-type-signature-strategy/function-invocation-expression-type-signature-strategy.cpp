//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/function-type-signature/function-type-signature.h"
#include "../../../../../../type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"

TypeSignature* FunctionInvocationExpressionTypeSignatureStrategy::create(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    functionInvocationExpression->getName()->print();
    auto functionTypeSignature = typeSignatureLookupTable->find(
            functionInvocationExpression->getName()->getId()
    );
    if (!functionTypeSignature->is(FUNCTION_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    return new FunctionInvocationTypeSignature((FunctionTypeSignature*)functionTypeSignature);
}