//
// Created by Johny Georges on 2024-05-18.
//

#include "literal-type-signature-lookup-table.h"

IntLiteralTypeSignature* LiteralTypeSignatureLookupTable::getIntLiteralTypeSignature() {
    return new IntLiteralTypeSignature();
}

FloatLiteralTypeSignature* LiteralTypeSignatureLookupTable::getFloatLiteralTypeSignature() {
    return new FloatLiteralTypeSignature();
}

CharLiteralTypeSignature* LiteralTypeSignatureLookupTable::getCharLiteralTypeSignature() {
    return new CharLiteralTypeSignature();
}

StringLiteralTypeSignature* LiteralTypeSignatureLookupTable::getStringLiteralTypeSignature() {
    return new StringLiteralTypeSignature();
}

BoolLiteralTypeSignature* LiteralTypeSignatureLookupTable::getBoolLiteralTypeSignature() {
    return new BoolLiteralTypeSignature();
}