//
// Created by Johny Georges on 2024-05-11.
//

#include "this-expression-type-signature-strategy.h"

TypeSignature* ThisExpressionTypeSignatureStrategy::create(ASTThisExpressionNode* thisExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    return typeSignatureLookupTable->find(thisExpression->getId());
}