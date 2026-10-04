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
#include "../../../../../src/core/type-signature/shared-type-signature/shared-type-signature.h"

namespace TypeSignatureFactory {
    static std::shared_ptr<IntLiteralTypeSignature> intLiteral = std::make_shared<IntLiteralTypeSignature>();
    static std::shared_ptr<FloatLiteralTypeSignature> floatLiteral = std::make_shared<FloatLiteralTypeSignature>();
    static std::shared_ptr<CharLiteralTypeSignature> charLiteral = std::make_shared<CharLiteralTypeSignature>();
    static std::shared_ptr<StringLiteralTypeSignature> stringLiteral = std::make_shared<StringLiteralTypeSignature>();
    static std::shared_ptr<BoolLiteralTypeSignature> boolLiteral = std::make_shared<BoolLiteralTypeSignature>();
    static std::shared_ptr<SharedTypeSignature> sharedIntLiteral = std::make_shared<SharedTypeSignature>(std::make_shared<IntLiteralTypeSignature>());
    static std::shared_ptr<SharedTypeSignature> sharedFloatLiteral = std::make_shared<SharedTypeSignature>(std::make_shared<FloatLiteralTypeSignature>());
    static std::shared_ptr<SharedTypeSignature> sharedCharLiteral = std::make_shared<SharedTypeSignature>(std::make_shared<CharLiteralTypeSignature>());
    static std::shared_ptr<SharedTypeSignature> sharedStringLiteral = std::make_shared<SharedTypeSignature>(std::make_shared<StringLiteralTypeSignature>());
    static std::shared_ptr<SharedTypeSignature> sharedBoolLiteral = std::make_shared<SharedTypeSignature>(std::make_shared<BoolLiteralTypeSignature>());
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
    static std::shared_ptr<ParameterListItemTypeSignature> createSharedIntParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::sharedIntLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createSharedFloatParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::sharedFloatLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createSharedCharParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::sharedCharLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createSharedStringParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::sharedStringLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createSharedBoolParameter(std::string name) {
        return std::make_shared<ParameterListItemTypeSignature>(name, TypeSignatureFactory::sharedBoolLiteral);
    }
    static std::shared_ptr<ParameterListItemTypeSignature> createParameter(std::string name, std::shared_ptr<TypeSignature> typeSignature) {
        return std::make_shared<ParameterListItemTypeSignature>(name, typeSignature);
    }

    static std::shared_ptr<AccessModifierTypeSignature> publicAccess = std::make_shared<AccessModifierTypeSignature>(PUBLIC_ACCESS_MODIFIER_TYPE);
    static std::shared_ptr<AccessModifierTypeSignature> protectedAccess = std::make_shared<AccessModifierTypeSignature>(PROTECTED_ACCESS_MODIFIER_TYPE);
    static std::shared_ptr<AccessModifierTypeSignature> privateAccess = std::make_shared<AccessModifierTypeSignature>(PRIVATE_ACCESS_MODIFIER_TYPE);

};

#endif //JETLANG_TYPE_SIGNATURE_FACTORY_H
