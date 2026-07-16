//
// Created by Johny Georges on 2025-10-25.
//

#include "shared-ptr-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../type-signature/shared-type-signature/shared-type-signature.h"

std::optional<std::shared_ptr<FunctionTypeSignature>> SharedPtrPrototypeTypeSignatureMap::find(std::string id, std::shared_ptr<TypeSignature> refType) {

    if (id == "sharesWith") {
        auto sharesWithTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                        std::make_shared<ParameterListItemTypeSignature>("other", std::make_shared<SharedTypeSignature>(refType))
                }),
                std::make_shared<BoolLiteralTypeSignature>()
        );
        sharesWithTypeSignature->markAsPrototype();
        return sharesWithTypeSignature;
    }

    if (id == "refCount") {
        auto refCountTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(),
                std::make_shared<IntLiteralTypeSignature>()
        );
        refCountTypeSignature->markAsPrototype();
        return refCountTypeSignature;
    }

    return {};
}