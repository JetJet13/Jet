//
// Created by Johny Georges on 2024-05-18.
//

#include "literal-type-signature-lookup-table.h"

std::shared_ptr<IntLiteralTypeSignature> LiteralTypeSignatureLookupTable::getIntLiteralTypeSignature() {
    return std::make_shared<IntLiteralTypeSignature>();
}

std::shared_ptr<FloatLiteralTypeSignature> LiteralTypeSignatureLookupTable::getFloatLiteralTypeSignature() {
    return std::make_shared<FloatLiteralTypeSignature>();
}

std::shared_ptr<CharLiteralTypeSignature> LiteralTypeSignatureLookupTable::getCharLiteralTypeSignature() {
    return std::make_shared<CharLiteralTypeSignature>();
}

std::shared_ptr<StringLiteralTypeSignature> LiteralTypeSignatureLookupTable::getStringLiteralTypeSignature() {
    return std::make_shared<StringLiteralTypeSignature>();
}

std::shared_ptr<BoolLiteralTypeSignature> LiteralTypeSignatureLookupTable::getBoolLiteralTypeSignature() {
    return std::make_shared<BoolLiteralTypeSignature>();
}