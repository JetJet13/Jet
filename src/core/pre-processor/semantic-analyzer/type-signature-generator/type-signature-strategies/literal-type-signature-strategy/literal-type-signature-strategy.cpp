//
// Created by Johny Georges on 2024-05-13.
//

#include "literal-type-signature-strategy.h"
#include "../../../../../type-signature/unknown-type-signature/unknown-type-signature.h"


LiteralTypeSignature* LiteralTypeSignatureStrategy::create(ASTLiteralNode* literalNode, TypeSignatureLookupTable* typeSignatureLookupTable) {
    auto literalSymbol = literalNode->getLiteral()->getToken()->getSymbol();
    if (literalSymbol->isInt()) {
        return typeSignatureLookupTable->getIntLiteralTypeSignature();
    } else if (literalSymbol->isFloat()) {
        return typeSignatureLookupTable->getFloatLiteralTypeSignature();
    } else if (literalSymbol->isChar()) {
        return typeSignatureLookupTable->getCharLiteralTypeSignature();
    } else if (literalSymbol->isString()) {
        return typeSignatureLookupTable->getStringLiteralTypeSignature();
    } else if (literalSymbol->isBoolean()) {
        return typeSignatureLookupTable->getBoolLiteralTypeSignature();
    } else {
        throw std::invalid_argument("unknown literal node");
    }
}