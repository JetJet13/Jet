// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2026-03-21.
//

#include "string-prototype-type-signature-map.h"
#include "../../../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../type-signature/void-type-signature/void-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/string-literal-type-signature.h"
#include "../../../../../type-signature/literal-type-signature/char-literal-type-signature.h"

std::optional<std::shared_ptr<FunctionTypeSignature>> StringPrototypeTypeSignatureMap::find(std::string id) {
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
                std::make_shared<StringLiteralTypeSignature>()
        );
        takeTypeSignature->markAsPrototype();
        return takeTypeSignature;
    }

    // will support head and last once we add null support
//    if (id == "head" || id == "last") {
//        auto headTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(), std::make_shared<CharLiteralTypeSignature>());
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

    if (id == "at") {
        auto atTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(std::vector {
                std::make_shared<ParameterListItemTypeSignature>("index", std::make_shared<IntLiteralTypeSignature>())
        }), std::make_shared<CharLiteralTypeSignature>());
        atTypeSignature->markAsPrototype();
        return atTypeSignature;
    }

    if (id == "tail") {
        auto tailTypeSignature = std::make_shared<FunctionTypeSignature>(std::make_shared<ParameterListTypeSignature>(), std::make_shared<StringLiteralTypeSignature>());
        tailTypeSignature->markAsPrototype();
        return tailTypeSignature;
    }

    if (id == "append" || id == "prepend") {
        auto appendTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
               std::make_shared<ParameterListItemTypeSignature>("value", std::make_shared<CharLiteralTypeSignature>())
            }),
            std::make_shared<VoidTypeSignature>()
        );
        appendTypeSignature->markAsPrototype();
        return appendTypeSignature;
    }

    return {};
}