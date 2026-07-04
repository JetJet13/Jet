//
// Created by Johny Georges on 2024-05-09.
//

#include "array-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/array-type-signature/array-type-signature.h"

void ArrayTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTArrayTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getElementType(), context, scope);
    node->setTypeSignature(std::make_shared<ArrayTypeSignature>(node->getElementType()->getTypeSignature()));
}