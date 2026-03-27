//
// Created by Johny Georges on 2026-03-21.
//

#include "string-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../type-signature/void-type-signature/void-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/string-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/char-literal-type-signature.h"

std::optional<FunctionTypeSignature*> StringPrototypeTypeSignatureMap::find(std::string id) {
    if (id == "drop" || id == "dropLast") {
        auto dropTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature("num", new IntLiteralTypeSignature())
                }),
                new VoidTypeSignature()
        );
        dropTypeSignature->markAsPrototype();
        return dropTypeSignature;
    }

    if (id == "take" || id == "takeLast") {
        auto takeTypeSignature = new FunctionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("num", new IntLiteralTypeSignature())
                }),
                new StringLiteralTypeSignature()
        );
        takeTypeSignature->markAsPrototype();
        return takeTypeSignature;
    }

    // will support head and last once we add null support
//    if (id == "head" || id == "last") {
//        auto headTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature(), new CharLiteralTypeSignature());
//        headTypeSignature->markAsPrototype();
//        return headTypeSignature;
//    }

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

    if (id == "at") {
        auto atTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("index", new IntLiteralTypeSignature())
        }), new CharLiteralTypeSignature());
        atTypeSignature->markAsPrototype();
        return atTypeSignature;
    }

    if (id == "tail") {
        auto tailTypeSignature = new FunctionTypeSignature(new ParameterListTypeSignature(), new StringLiteralTypeSignature());
        tailTypeSignature->markAsPrototype();
        return tailTypeSignature;
    }

    if (id == "append" || id == "prepend") {
        auto appendTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
               new ParameterListItemTypeSignature("value", new CharLiteralTypeSignature())
            }),
            new VoidTypeSignature()
        );
        appendTypeSignature->markAsPrototype();
        return appendTypeSignature;
    }

    return {};
}