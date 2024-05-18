//
// Created by Johny Georges on 2024-05-13.
//

#include "literal-type-signature-strategy.h"
#include "../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"


LiteralTypeSignature* LiteralTypeSignatureStrategy::create(ASTLiteralNode* literalNode, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable) {
    auto literalSymbol = literalNode->getLiteral()->getToken()->getSymbol();
    if (literalSymbol->isInt()) {
        return literalTypeSignatureLookupTable->getIntLiteralTypeSignature();
    } else if (literalSymbol->isFloat()) {
        return literalTypeSignatureLookupTable->getFloatLiteralTypeSignature();
    } else if (literalSymbol->isChar()) {
        return literalTypeSignatureLookupTable->getCharLiteralTypeSignature();
    } else if (literalSymbol->isString()) {
        return literalTypeSignatureLookupTable->getStringLiteralTypeSignature();
    } else if (literalSymbol->isBoolean()) {
        return literalTypeSignatureLookupTable->getBoolLiteralTypeSignature();
    } else {
        throw std::invalid_argument("unknown literal node");
    }
}