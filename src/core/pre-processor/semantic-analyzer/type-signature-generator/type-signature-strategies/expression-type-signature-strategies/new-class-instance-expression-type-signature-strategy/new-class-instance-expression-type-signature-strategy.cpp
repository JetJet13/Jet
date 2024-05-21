//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"

TypeSignature* NewClassInstanceExpressionTypeSignatureStrategy::create(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(
            newClassInstanceExpression
            ->getClassName()
            ->getId()
    );
    if (customTypeSignature->is(CLASS_TYPE_SOURCE)) {
        return new ClassInstanceTypeSignature((ClassTypeSignature*)customTypeSignature);
    }
    return new UnknownTypeSignature();
}