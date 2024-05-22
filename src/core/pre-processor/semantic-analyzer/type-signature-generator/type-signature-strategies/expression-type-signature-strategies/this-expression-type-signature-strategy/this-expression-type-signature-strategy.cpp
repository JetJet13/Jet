//
// Created by Johny Georges on 2024-05-11.
//

#include "this-expression-type-signature-strategy.h"

void ThisExpressionTypeSignatureStrategy::assign(ASTThisExpressionNode* thisExpression, TypeSignatureLookupTable* typeSignatureLookupTable) {
    thisExpression->setTypeSignature(typeSignatureLookupTable->find(thisExpression->getId()));
}