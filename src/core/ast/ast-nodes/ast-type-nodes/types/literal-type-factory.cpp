//
// Created by Johny Georges on 2024-04-30.
//

#include "literal-type-factory.h"

namespace LiteralTypeFactory {
    LiteralType* createIntLiteralType() {
        return new LiteralType(INT_TYPE);
    }

    LiteralType* createFloatLiteralType() {
        return new LiteralType(FLOAT_TYPE);
    }

    LiteralType* createCharLiteralType() {
        return new LiteralType(CHAR_TYPE);
    }

    LiteralType* createStringLiteralType() {
        return new LiteralType(STRING_TYPE);
    }

    LiteralType* createBooleanLiteralType() {
        return new LiteralType(BOOL_TYPE);
    }

    LiteralType* createNotNullLiteralType() {
        return new LiteralType(NOT_NULL_TYPE);
    }

    LiteralType* createVoidLiteralType() {
        return new LiteralType(VOID_TYPE);
    }
}