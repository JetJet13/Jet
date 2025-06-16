//
// Created by Johny Georges on 2025-06-16.
//

#include "array-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/array-type-signature/array-type-signature.h"

std::optional<FunctionTypeSignature*> ArrayPrototypeTypeSignatureMap::find(std::string id, TypeSignature* elementType) {
    if (id == "drop" || id == "dropLast") {
        return new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("num", new IntLiteralTypeSignature())
                }),
                new ArrayTypeSignature(elementType)
        );
    }

    if (id == "take" || id == "takeLast") {
        return new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("num", new IntLiteralTypeSignature())
                }),
                new ArrayTypeSignature(elementType)
        );
    }

    if (id == "append" || id == "prepend") {
        return new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("value", elementType)
                }),
                new ArrayTypeSignature(elementType)
        );
    }

    if (id == "head" || id == "last") {
        return new FunctionTypeSignature(new ParameterListTypeSignature(), elementType);
    }

    if (id == "tail") {
        return new FunctionTypeSignature(new ParameterListTypeSignature(), new ArrayTypeSignature(elementType));
    }

    return {};
}