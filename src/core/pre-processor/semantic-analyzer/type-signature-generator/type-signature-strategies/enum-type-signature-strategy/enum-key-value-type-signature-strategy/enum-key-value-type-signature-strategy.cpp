//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-key-value-type-signature-strategy.h"
#include "../../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"


void EnumKeyValueTypeSignatureStrategy::assign(std::shared_ptr<ASTEnumKeyValueNode> node, std::shared_ptr<TypeSignatureContext> context, TypeSignatureStrategyProvider* strategyMap) {
    if (node->getValue()) {
        strategyMap->assignTypeSignatureFor(node->getValue().value(), context);
        node->setTypeSignature(node->getValue().value()->getLiteralTypeSignature());
        return;
    }
    node->setTypeSignature(std::make_shared<DefaultEnumKeyValueTypeSignature>());
}