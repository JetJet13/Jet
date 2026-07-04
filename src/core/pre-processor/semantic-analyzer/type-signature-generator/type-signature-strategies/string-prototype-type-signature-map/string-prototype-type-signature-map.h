//
// Created by Johny Georges on 2026-03-21.
//

#ifndef JETLANG_STRING_PROTOTYPE_TYPE_SIGNATURE_MAP_H
#define JETLANG_STRING_PROTOTYPE_TYPE_SIGNATURE_MAP_H

#include <vector>
#include "../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

class StringPrototypeTypeSignatureMap {
public:
    std::optional<std::shared_ptr<FunctionTypeSignature>> find(std::string id);
};

#endif //JETLANG_STRING_PROTOTYPE_TYPE_SIGNATURE_MAP_H
