//
// Created by Johny Georges on 2024-05-18.
//

#include "literal-type-signature-lookup-table.h"

LiteralTypeSignatureLookupTable::LiteralTypeSignatureLookupTable() {
    _intLiteralTypeSignature = IntLiteralTypeSignature();
    _floatLiteralTypeSignature = FloatLiteralTypeSignature();
    _charLiteralTypeSignature = CharLiteralTypeSignature();
    _stringLiteralTypeSignature = StringLiteralTypeSignature();
    _boolLiteralTypeSignature = BoolLiteralTypeSignature();
}

IntLiteralTypeSignature* LiteralTypeSignatureLookupTable::getIntLiteralTypeSignature() {
    return &_intLiteralTypeSignature;
}

FloatLiteralTypeSignature* LiteralTypeSignatureLookupTable::getFloatLiteralTypeSignature() {
    return &_floatLiteralTypeSignature;
}

CharLiteralTypeSignature* LiteralTypeSignatureLookupTable::getCharLiteralTypeSignature() {
    return &_charLiteralTypeSignature;
}

StringLiteralTypeSignature* LiteralTypeSignatureLookupTable::getStringLiteralTypeSignature() {
    return &_stringLiteralTypeSignature;
}

BoolLiteralTypeSignature* LiteralTypeSignatureLookupTable::getBoolLiteralTypeSignature() {
    return &_boolLiteralTypeSignature;
}