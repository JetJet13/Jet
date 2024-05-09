//
// Created by Johny Georges on 2024-05-07.
//

#include "class-method-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../../../../../type-signature/void-type-signature/void-type-signature.h"

TypeSignature* ClassMethodInvocationExpressionTypeSignatureStrategy::create(ASTClassMethodInvocationExpressionNode* classMethodInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto classMethodTypeSignature = typeSignatureLookupTable->find(classMethodInvocationExpression->getName()->getId());
    if (!classMethodTypeSignature->hasTypeSource(CLASS_METHOD_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    auto classMethodReturnType = ((ClassMethodTypeSignature*)classMethodTypeSignature)->getReturnType();
    if (classMethodReturnType) {
        return classMethodReturnType.value();
    }
    return new VoidTypeSignature();
}