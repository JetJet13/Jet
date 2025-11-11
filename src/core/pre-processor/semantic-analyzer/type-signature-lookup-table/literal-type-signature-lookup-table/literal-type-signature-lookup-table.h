//
// Created by Johny Georges on 2024-05-18.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_LOOKUP_TABLE_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_LOOKUP_TABLE_H

#include "../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../type-signature/literal-type-signature/float-literal-type-signature.h"
#include "../../../../type-signature/literal-type-signature/char-literal-type-signature.h"
#include "../../../../type-signature/literal-type-signature/string-literal-type-signature.h"
#include "../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"

class LiteralTypeSignatureLookupTable {
public:
    IntLiteralTypeSignature* getIntLiteralTypeSignature();
    FloatLiteralTypeSignature* getFloatLiteralTypeSignature();
    CharLiteralTypeSignature* getCharLiteralTypeSignature();
    StringLiteralTypeSignature* getStringLiteralTypeSignature();
    BoolLiteralTypeSignature* getBoolLiteralTypeSignature();
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_LOOKUP_TABLE_H
