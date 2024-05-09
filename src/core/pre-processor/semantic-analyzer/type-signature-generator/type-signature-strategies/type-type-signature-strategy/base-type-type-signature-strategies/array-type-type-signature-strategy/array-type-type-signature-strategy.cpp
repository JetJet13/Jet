//
// Created by Johny Georges on 2024-05-09.
//

#include "array-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* ArrayTypeTypeSignatureStrategy::create(ASTArrayTypeNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto intLiteralTypeSignature = strategyMap->getTypeSignatureFor(node->getSize());
    if (!intLiteralTypeSignature->hasTypeSource(INT_LITERAL_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    return new ArrayTypeSignature(strategyMap->getTypeSignatureFor(node->getElementType()), (IntLiteralTypeSignature*)intLiteralTypeSignature);
}