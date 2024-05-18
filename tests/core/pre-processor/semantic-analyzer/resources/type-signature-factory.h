//
// Created by Johny Georges on 2024-05-17.
//

#ifndef JETLANG_TYPE_SIGNATURE_FACTORY_H
#define JETLANG_TYPE_SIGNATURE_FACTORY_H

#include "../../../../../src/core/type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../src/core/type-signature/literal-type-signature/float-literal-type-signature.h"
#include "../../../../../src/core/type-signature/literal-type-signature/char-literal-type-signature.h"
#include "../../../../../src/core/type-signature/literal-type-signature/string-literal-type-signature.h"
#include "../../../../../src/core/type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../src/core/type-signature/parameter-list-type-signature/parameter-list-item-type-signature/parameter-list-item-type-signature.h"

namespace TypeSignatureFactory {
    static IntLiteralTypeSignature* intLiteral = new IntLiteralTypeSignature();
    static FloatLiteralTypeSignature* floatLiteral = new FloatLiteralTypeSignature();
    static CharLiteralTypeSignature* charLiteral = new CharLiteralTypeSignature();
    static StringLiteralTypeSignature* stringLiteral = new StringLiteralTypeSignature();
    static BoolLiteralTypeSignature* boolLiteral = new BoolLiteralTypeSignature();

    static ParameterListItemTypeSignature* createIntParameter(std::string name) {
        return new ParameterListItemTypeSignature(name, TypeSignatureFactory::intLiteral);
    }
    static ParameterListItemTypeSignature* createFloatParameter(std::string name) {
        return new ParameterListItemTypeSignature(name, TypeSignatureFactory::floatLiteral);
    }
    static ParameterListItemTypeSignature* createCharParameter(std::string name) {
        return new ParameterListItemTypeSignature(name, TypeSignatureFactory::charLiteral);
    }
    static ParameterListItemTypeSignature* createStringParameter(std::string name) {
        return new ParameterListItemTypeSignature(name, TypeSignatureFactory::stringLiteral);
    }
    static ParameterListItemTypeSignature* createBoolParameter(std::string name) {
        return new ParameterListItemTypeSignature(name, TypeSignatureFactory::boolLiteral);
    }
};

#endif //JETLANG_TYPE_SIGNATURE_FACTORY_H
