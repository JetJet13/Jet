//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-key-value-type-signature-strategy.h"
#include "../../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"


void EnumKeyValueTypeSignatureStrategy::assign(ASTEnumKeyValueNode* node, TypeSignatureStrategyProvider* strategyMap) {
    if (node->getValue()) {
        strategyMap->assignTypeSignatureForLiteral(node->getValue().value());
        node->setTypeSignature(node->getValue().value()->getTypeSignature());
    }
    node->setTypeSignature(new DefaultEnumKeyValueTypeSignature());
}