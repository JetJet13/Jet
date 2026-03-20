//
// Created by Johny Georges on 2024-05-09.
//

#include "array-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/array-type-signature/array-type-signature.h"

void ArrayTypeTypeSignatureStrategy::assign(ASTArrayTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getElementType(), context, scope);
    node->setTypeSignature(new ArrayTypeSignature(node->getElementType()->getTypeSignature()));
}