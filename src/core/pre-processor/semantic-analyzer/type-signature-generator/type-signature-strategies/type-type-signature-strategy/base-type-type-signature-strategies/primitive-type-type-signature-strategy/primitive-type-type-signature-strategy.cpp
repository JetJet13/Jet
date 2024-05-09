//
// Created by Johny Georges on 2024-05-09.
//

#include "primitive-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../type-signature/literal-type-signature/types/literal-type-signature-name.h"

TypeSignature* PrimitiveTypeTypeSignatureStrategy::create(ASTPrimitiveTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto symbol = node->getLexeme()->getToken()->getSymbol();
    if (symbol->isIntType()) {
        return typeSignatureLookupTable->find(LiteralTypeSignatureName::INT);
    } else if (symbol->isFloatType()) {
        return typeSignatureLookupTable->find(LiteralTypeSignatureName::FLOAT);
    } else if (symbol->isCharType()) {
        return typeSignatureLookupTable->find(LiteralTypeSignatureName::CHAR);
    } else if (symbol->isStringType()) {
        return typeSignatureLookupTable->find(LiteralTypeSignatureName::STRING);
    } else if (symbol->isBooleanType()) {
        return typeSignatureLookupTable->find(LiteralTypeSignatureName::BOOL);
    } else {
        return new InvalidTypeSignature();
    }
}