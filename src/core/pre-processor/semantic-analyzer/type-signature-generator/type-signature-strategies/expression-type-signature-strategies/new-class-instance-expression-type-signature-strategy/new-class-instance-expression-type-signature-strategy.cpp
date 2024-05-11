//
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"

TypeSignature* NewClassInstanceExpressionTypeSignatureStrategy::create(ASTNewClassInstanceExpressionNode* newClassInstanceExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    return typeSignatureLookupTable->find(newClassInstanceExpression->getClassName()->getId());
}