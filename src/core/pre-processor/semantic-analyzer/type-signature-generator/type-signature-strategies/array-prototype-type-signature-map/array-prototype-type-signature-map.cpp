//
// Created by Johny Georges on 2025-06-16.
//

#include "array-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"

std::optional<FunctionTypeSignature*> ArrayPrototypeTypeSignatureMap::find(std::string id, TypeSignature* elementType) {
    if (id == "drop" || id == "dropLast") {
        auto dropTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("num", new IntLiteralTypeSignature())
                }),
                new ArrayTypeSignature(elementType)
        );
        dropTypeSignature->markAsPrototype();
        return dropTypeSignature;
    }

    if (id == "take" || id == "takeLast") {
        auto takeTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("num", new IntLiteralTypeSignature())
                }),
                new ArrayTypeSignature(elementType)
        );
        takeTypeSignature->markAsPrototype();
        return takeTypeSignature;
    }

    if (id == "append" || id == "prepend") {
        auto appendTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("value", elementType)
                }),
                new ArrayTypeSignature(elementType)
        );
        appendTypeSignature->markAsPrototype();
        return appendTypeSignature;
    }

    if (id == "head" || id == "last") {
        auto headTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature(), elementType);
        headTypeSignature->markAsPrototype();
        return headTypeSignature;
    }

    if (id == "size") {
        auto sizeTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature(), new IntLiteralTypeSignature());
        sizeTypeSignature->markAsPrototype();
        return sizeTypeSignature;
    }

    if (id == "empty") {
        auto emptyTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature(), new BoolLiteralTypeSignature());
        emptyTypeSignature->markAsPrototype();
        return emptyTypeSignature;
    }

    if (id == "tail") {
        auto tailTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature(), new ArrayTypeSignature(elementType));
        tailTypeSignature->markAsPrototype();
        return tailTypeSignature;
    }

    return {};
}