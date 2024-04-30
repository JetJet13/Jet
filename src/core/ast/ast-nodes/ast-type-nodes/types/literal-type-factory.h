//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_LITERAL_TYPE_FACTORY_H
#define JETLANG_LITERAL_TYPE_FACTORY_H

#include "literal-type.h"

namespace LiteralTypeFactory {
    LiteralType* createIntLiteralType();
    LiteralType* createFloatLiteralType();
    LiteralType* createCharLiteralType();
    LiteralType* createStringLiteralType();
    LiteralType* createBooleanLiteralType();
    LiteralType* createNotNullLiteralType();
    LiteralType* createVoidLiteralType();
}

#endif //JETLANG_LITERAL_TYPE_FACTORY_H
