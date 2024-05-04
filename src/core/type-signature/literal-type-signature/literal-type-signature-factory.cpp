//
// Created by Johny Georges on 2024-04-30.
//

#include "literal-type-signature-factory.h"

namespace LiteralTypeSignatureFactory {
    LiteralTypeSignature* createIntLiteralType() {
        return new LiteralTypeSignature(INT_TYPE);
    }

    LiteralTypeSignature* createFloatLiteralType() {
        return new LiteralTypeSignature(FLOAT_TYPE);
    }

    LiteralTypeSignature* createCharLiteralType() {
        return new LiteralTypeSignature(CHAR_TYPE);
    }

    LiteralTypeSignature* createStringLiteralType() {
        return new LiteralTypeSignature(STRING_TYPE);
    }

    LiteralTypeSignature* createBooleanLiteralType() {
        return new LiteralTypeSignature(BOOL_TYPE);
    }

    LiteralTypeSignature* createNotNullLiteralType() {
        return new LiteralTypeSignature(NOT_NULL_TYPE);
    }

    LiteralTypeSignature* createVoidLiteralType() {
        return new LiteralTypeSignature(VOID_TYPE);
    }
}