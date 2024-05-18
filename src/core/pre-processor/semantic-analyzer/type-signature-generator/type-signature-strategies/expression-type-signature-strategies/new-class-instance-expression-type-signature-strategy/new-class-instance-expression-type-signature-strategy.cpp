//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"

TypeSignature* NewClassInstanceExpressionTypeSignatureStrategy::create(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(
            tokenTable->getIdentifier(
                    newClassInstanceExpression
                            ->getClassName()
                            ->getLexeme()
                            ->getToken()
                            ->getValueId()
                            .value()
            ).value()
    );
    if (customTypeSignature->is(CLASS_TYPE_SOURCE)) {
        return new ClassInstanceTypeSignature((ClassTypeSignature*)customTypeSignature);
    }
    return new UnknownTypeSignature();
}