//
// Created by Johny Georges on 2025-02-08.
//

#include "ref-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void RefTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTRefTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getRefType(), context, scope);
    node->setTypeSignature(std::make_shared<RefTypeSignature>(node->getRefType()->getTypeSignature()->convertToVariableTypeSignature()));
}