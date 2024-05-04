//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_FACTORY_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_FACTORY_H

#include "literal-type-signature.h"

namespace LiteralTypeSignatureFactory {
    LiteralTypeSignature* createIntLiteralType();
    LiteralTypeSignature* createFloatLiteralType();
    LiteralTypeSignature* createCharLiteralType();
    LiteralTypeSignature* createStringLiteralType();
    LiteralTypeSignature* createBooleanLiteralType();
    LiteralTypeSignature* createNotNullLiteralType();
    LiteralTypeSignature* createVoidLiteralType();
}

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_FACTORY_H
