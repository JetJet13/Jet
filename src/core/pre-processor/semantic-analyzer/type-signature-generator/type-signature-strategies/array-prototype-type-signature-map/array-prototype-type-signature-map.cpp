//
// Created by Johny Georges on 2025-06-16.
//

#include "array-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../type-signature/void-type-signature/void-type-signature.h"

std::optional<std::shared_ptr<FunctionTypeSignature>> ArrayPrototypeTypeSignatureMap::find(std::string id, std::shared_ptr<TypeSignature> elementType) {
    if (id == "drop" || id == "dropLast") {
        auto dropTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                    std::make_shared<ParameterListItemTypeSignature>("num", std::make_shared<IntLiteralTypeSignature>())
                }),
                std::make_shared<VoidTypeSignature>()
        );
        dropTypeSignature->markAsPrototype();
        return dropTypeSignature;
    }

    if (id == "take" || id == "takeLast") {
        auto takeTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                    std::make_shared<ParameterListItemTypeSignature>("num", std::make_shared<IntLiteralTypeSignature>())
                }),
                std::make_shared<ArrayTypeSignature>(elementType)
        );
        takeTypeSignature->markAsPrototype();
        return takeTypeSignature;
    }

    if (id == "append" || id == "prepend") {
        auto appendTypeSignature = std::make_shared<FunctionTypeSignature>(
                std::make_shared<ParameterListTypeSignature>(std::vector {
                    std::make_shared<ParameterListItemTypeSignature>("value", elementType)
                }),
                std::make_shared<VoidTypeSignature>()
        );
        appendTypeSignature->markAsPrototype();
        return appendTypeSignature;
    }

// will support head and last once we add null support
//    if (id == "head" || id == "last") {
//        auto headTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(), elementType);
//        headTypeSignature->markAsPrototype();
//        return headTypeSignature;
//    }

    if (id == "size") {
        auto sizeTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(), std::make_shared<IntLiteralTypeSignature>());
        sizeTypeSignature->markAsPrototype();
        return sizeTypeSignature;
    }

    if (id == "empty") {
        auto emptyTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(), std::make_shared<BoolLiteralTypeSignature>());
        emptyTypeSignature->markAsPrototype();
        return emptyTypeSignature;
    }

    if (id == "tail") {
        auto tailTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(), std::make_shared<ArrayTypeSignature>(elementType));
        tailTypeSignature->markAsPrototype();
        return tailTypeSignature;
    }

    return {};
}