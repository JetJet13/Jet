//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void NewClassInstanceExpressionTypeSignatureStrategy::assign(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto customTypeSignature = typeSignatureLookupTable->find(
            newClassInstanceExpression
            ->getClassName()
            ->getId()
    );
    if (customTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        newClassInstanceExpression->setTypeSignature(new ClassInstanceTypeSignature((ClassTypeSignature*)customTypeSignature));
    } else {
        newClassInstanceExpression->setTypeSignature(new UnknownTypeSignature());
    }
}