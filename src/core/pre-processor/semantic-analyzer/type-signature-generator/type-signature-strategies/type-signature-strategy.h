//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../type-signature/type-signature.h"
#include "../../../../ast/ast-nodes/ast-node.h"

template<class T>
class TypeSignatureStrategy {
public:
    virtual TypeSignature* generate(T* node) = 0;
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_H
