//
// Created by Johny Georges on 2024-05-09.
//

#include "int-literal-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* IntLiteralTypeTypeSignatureStrategy::create(ASTIntLiteralTypeNode* node, TokenTable* tokenTable) {
    auto intLiteralTypeValueId = node->getLexeme()->getToken()->getValueId();
    if (intLiteralTypeValueId && tokenTable->getInt(intLiteralTypeValueId.value())) {
        auto intLiteralValue = tokenTable->getInt(intLiteralTypeValueId.value()).value();
        if (intLiteralValue < 0) {
            return new InvalidTypeSignature();
        }
        return new IntLiteralTypeSignature(intLiteralValue);
    }
    return new InvalidTypeSignature();
}