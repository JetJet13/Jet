//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

void NewClassInstanceExpressionTypeSignatureStrategy::assign(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(
            newClassInstanceExpression
            ->getClassName()
            ->getId()
    );
    if (customTypeSignature->is(CLASS_TYPE_SOURCE)) {
        newClassInstanceExpression->setTypeSignature(new ClassInstanceTypeSignature((ClassTypeSignature*)customTypeSignature));
        return;
    }
    newClassInstanceExpression->setTypeSignature(new UnknownTypeSignature());
}