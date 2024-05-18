//
// Created by Johny Georges on 2024-05-09.
//

#include "primitive-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* PrimitiveTypeTypeSignatureStrategy::create(ASTPrimitiveTypeNode* node, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable) {
    auto symbol = node->getLexeme()->getToken()->getSymbol();
    if (symbol->isIntType()) {
        return literalTypeSignatureLookupTable->getIntLiteralTypeSignature();
    } else if (symbol->isFloatType()) {
        return literalTypeSignatureLookupTable->getFloatLiteralTypeSignature();
    } else if (symbol->isCharType()) {
        return literalTypeSignatureLookupTable->getCharLiteralTypeSignature();
    } else if (symbol->isStringType()) {
        return literalTypeSignatureLookupTable->getStringLiteralTypeSignature();
    } else if (symbol->isBooleanType()) {
        return literalTypeSignatureLookupTable->getBoolLiteralTypeSignature();
    } else {
        return new InvalidTypeSignature();
    }
}