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
#include "../../../../../src/core/type-signature/ref-type-signature/ref-type-signature.h"

namespace TypeSignatureFactory {
    static std::shared_ptr<IntLiteralTypeSignature> intLiteral = std::make_shared<IntLiteralTypeSignature>();
    static std::shared_ptr<FloatLiteralTypeSignature> floatLiteral = std::make_shared<FloatLiteralTypeSignature>();
    static std::shared_ptr<CharLiteralTypeSignature> charLiteral = std::make_shared<CharLiteralTypeSignature>();
    static std::shared_ptr<StringLiteralTypeSignature> stringLiteral = std::make_shared<StringLiteralTypeSignature>();
    static std::shared_ptr<BoolLiteralTypeSignature> boolLiteral = std::make_shared<BoolLiteralTypeSignature>();
    static std::shared_ptr<RefTypeSignature> refIntLiteral = std::make_shared<RefTypeSignature>(std::make_shared<IntLiteralTypeSignature>());
    static std::shared_ptr<RefTypeSignature> refFloatLiteral = std::make_shared<RefTypeSignature>(std::make_shared<FloatLiteralTypeSignature>());
    static std::shared_ptr<RefTypeSignature> refCharLiteral = std::make_shared<RefTypeSignature>(std::make_shared<CharLiteralTypeSignature>());
    static std::shared_ptr<RefTypeSignature> refStringLiteral = std::make_shared<RefTypeSignature>(std::make_shared<StringLiteralTypeSignature>());
    static std::shared_ptr<RefTypeSignature> refBoolLiteral = std::make_shared<RefTypeSignature>(std::make_shared<BoolLiteralTypeSignature>());
    static std::shared_ptr<ParameterListItemTypeSignature> createLambdaScopeParameter() {
        return ParameterListItemTypeSignature::createScopeParameter();
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createIntParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::intLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createFloatParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::floatLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createCharParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::charLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createStringParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::stringLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createBoolParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::boolLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createRefIntParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::refIntLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createRefFloatParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::refFloatLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createRefCharParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::refCharLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createRefStringParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::refStringLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createRefBoolParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::refBoolLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createParameter(std::string name, std::shared_ptr<TypeSignature> typeSignature) {
        return std::make_shared<ParameterListItemTypeSignature>(name, typeSignature);
    }

    static std::shared_ptr<AccessModifierTypeSignature> publicAccess = std::make_shared<AccessModifierTypeSignature>(PUBLIC_ACCESS_MODIFIER_TYPE);
    static std::shared_ptr<AccessModifierTypeSignature> protectedAccess = std::make_shared<AccessModifierTypeSignature>(PROTECTED_ACCESS_MODIFIER_TYPE);
    static std::shared_ptr<AccessModifierTypeSignature> privateAccess = std::make_shared<AccessModifierTypeSignature>(PRIVATE_ACCESS_MODIFIER_TYPE);

};

#endif //JETLANG_TYPE_SIGNATURE_FACTORY_H
