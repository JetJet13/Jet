//
// Created by Johny Georges on 2025-10-25.
//

#include "ref-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../../../type-signature/void-type-signature/void-type-signature.h"

std::optional<std::shared_ptr<FunctionTypeSignature>> RefPrototypeTypeSignatureMap::find(std::string id, std::shared_ptr<TypeSignature> refType) {
    if (id == "refOf") {
        auto refOfTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                       std::make_shared<ParameterListItemTypeSignature>("other", refType)
                }),
                std::make_shared<BoolLiteralTypeSignature>()
        );
        refOfTypeSignature->markAsPrototype();
        return refOfTypeSignature;
    }

    if (id == "srefWith" || id == "sameRefAs") {
        auto srefWithTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                        std::make_shared<ParameterListItemTypeSignature>("other", std::make_shared<RefTypeSignature>(refType))
                }),
                std::make_shared<BoolLiteralTypeSignature>()
        );
        srefWithTypeSignature->markAsPrototype();
        return srefWithTypeSignature;
    }

    if (id == "refCount") {
        auto refCountTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(),
                std::make_shared<IntLiteralTypeSignature>()
        );
        refCountTypeSignature->markAsPrototype();
        return refCountTypeSignature;
    }

    if (id == "setRefValue") {
        auto setRefValueTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                   std::make_shared<ParameterListItemTypeSignature>("value", refType)
                }),
                std::make_shared<VoidTypeSignature>()
        );
        setRefValueTypeSignature->markAsPrototype();
        return setRefValueTypeSignature;
    }

    return {};
}