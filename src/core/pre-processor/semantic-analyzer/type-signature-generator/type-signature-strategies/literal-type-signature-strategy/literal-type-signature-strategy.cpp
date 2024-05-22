//
// Created by Johny Georges on 2024-05-13.
//

#include "literal-type-signature-strategy.h"


void LiteralTypeSignatureStrategy::assign(ASTLiteralNode* literalNode, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable) {
    auto literalSymbol = literalNode->getLiteral()->getToken()->getSymbol();
    if (literalSymbol->isInt()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getIntLiteralTypeSignature());
    } else if (literalSymbol->isFloat()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getFloatLiteralTypeSignature());
    } else if (literalSymbol->isChar()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getCharLiteralTypeSignature());
    } else if (literalSymbol->isString()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getStringLiteralTypeSignature());
    } else if (literalSymbol->isBoolean()) {
        literalNode->setTypeSignature(literalTypeSignatureLookupTable->getBoolLiteralTypeSignature());
    } else {
        throw std::invalid_argument("unknown literal node");
    }
}