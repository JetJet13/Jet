//
// Created by Johny Georges on 2025-10-25.
//

#include "ref-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../type-signature/ref-type-signature/ref-type-signature.h"

std::optional<FunctionTypeSignature*> RefPrototypeTypeSignatureMap::find(std::string id, TypeSignature* refType) {
    if (id == "refOf") {
        auto refOfTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature("other", refType)
                }),
                new BoolLiteralTypeSignature()
        );
        refOfTypeSignature->markAsPrototype();
        return refOfTypeSignature;
    }

    if (id == "srefWith") {
        auto srefWithTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                        new ParameterListItemTypeSignature("other", new RefTypeSignature(refType))
                }),
                new BoolLiteralTypeSignature()
        );
        srefWithTypeSignature->markAsPrototype();
        return srefWithTypeSignature;
    }

    return {};
}