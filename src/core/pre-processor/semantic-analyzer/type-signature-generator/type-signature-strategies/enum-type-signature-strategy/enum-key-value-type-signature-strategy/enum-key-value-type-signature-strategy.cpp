//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-key-value-type-signature-strategy.h"
#include "../../../../../../type-signature/enum-type-signature/default-enum-key-value-type-signature/default-enum-key-value-type-signature.h"


LiteralTypeSignature* EnumKeyValueTypeSignatureStrategy::create(ASTEnumKeyValueNode* node, TypeSignatureStrategyProvider* strategyMap) {
    if (node->getValue()) {
        return strategyMap->getTypeSignatureForLiteral(node->getValue().value());
    }
    return new DefaultEnumKeyValueTypeSignature();
}