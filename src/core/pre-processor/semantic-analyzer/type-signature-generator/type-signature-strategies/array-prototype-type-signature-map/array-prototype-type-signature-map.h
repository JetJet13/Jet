//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_ARRAY_PROTOTYPE_TYPE_SIGNATURE_MAP_H
#define JETLANG_ARRAY_PROTOTYPE_TYPE_SIGNATURE_MAP_H

#include <vector>
#include "../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

class ArrayPrototypeTypeSignatureMap {
public:
    std::optional<FunctionTypeSignature*> find(std::string id, TypeSignature* elementType);
};

#endif //JETLANG_ARRAY_PROTOTYPE_TYPE_SIGNATURE_MAP_H
