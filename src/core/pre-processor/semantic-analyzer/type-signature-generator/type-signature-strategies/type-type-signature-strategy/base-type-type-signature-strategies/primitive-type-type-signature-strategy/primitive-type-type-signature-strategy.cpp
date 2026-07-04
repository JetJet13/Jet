//
// Created by Johny Georges on 2024-05-09.
//

#include "primitive-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void PrimitiveTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTPrimitiveTypeNode> node, LiteralTypeSignatureLookupTable* literalTypeSignatureLookupTable) {
    auto symbol = node->getLexeme()->getToken()->getSymbol();
    if (symbol->isIntType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getIntLiteralTypeSignature());
    } else if (symbol->isFloatType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getFloatLiteralTypeSignature());
    } else if (symbol->isCharType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getCharLiteralTypeSignature());
    } else if (symbol->isStringType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getStringLiteralTypeSignature());
    } else if (symbol->isBooleanType()) {
        node->setTypeSignature(literalTypeSignatureLookupTable->getBoolLiteralTypeSignature());
    } else {
        node->setTypeSignature(new InvalidTypeSignature());
    }
}