//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_REF_PROTOTYPE_TYPE_SIGNATURE_MAP_H
#define JETLANG_REF_PROTOTYPE_TYPE_SIGNATURE_MAP_H

#include <vector>
#include "../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

class RefPrototypeTypeSignatureMap {
public:
    std::optional<FunctionTypeSignature*> find(std::string id, TypeSignature* refType);
};

#endif //JETLANG_REF_PROTOTYPE_TYPE_SIGNATURE_MAP_H
