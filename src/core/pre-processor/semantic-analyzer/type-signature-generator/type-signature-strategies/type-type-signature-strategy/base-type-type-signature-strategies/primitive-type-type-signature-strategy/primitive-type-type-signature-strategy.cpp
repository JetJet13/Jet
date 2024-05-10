//
// Created by Johny Georges on 2024-05-09.
//

#include "primitive-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* PrimitiveTypeTypeSignatureStrategy::create(ASTPrimitiveTypeNode* node, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto symbol = node->getLexeme()->getToken()->getSymbol();
    if (symbol->isIntType()) {
        return typeSignatureLookupTable->getIntLiteralTypeSignature();
    } else if (symbol->isFloatType()) {
        return typeSignatureLookupTable->getFloatLiteralTypeSignature();
    } else if (symbol->isCharType()) {
        return typeSignatureLookupTable->getCharLiteralTypeSignature();
    } else if (symbol->isStringType()) {
        return typeSignatureLookupTable->getStringLiteralTypeSignature();
    } else if (symbol->isBooleanType()) {
        return typeSignatureLookupTable->getBoolLiteralTypeSignature();
    } else {
        return new InvalidTypeSignature();
    }
}