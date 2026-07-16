//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_SHARED_PTR_PROTOTYPE_TYPE_SIGNATURE_MAP_H
#define JETLANG_SHARED_PTR_PROTOTYPE_TYPE_SIGNATURE_MAP_H

#include <vector>
#include "../../../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

class SharedPtrPrototypeTypeSignatureMap {
public:
    std::optional<std::shared_ptr<FunctionTypeSignature>> find(std::string id, std::shared_ptr<TypeSignature> refType);
};

#endif //JETLANG_SHARED_PTR_PROTOTYPE_TYPE_SIGNATURE_MAP_H
