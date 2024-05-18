//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_H
#define JETLANG_TYPE_SIGNATURE_H

#include <vector>
#include <string>
#include "types/type-source.h"

class TypeSignature {
public:
    bool is(TypeSource other);
    bool isOneOf(std::vector<TypeSource> typeSources);
    bool isUnknown();
    bool isInvalid();
    bool isVoid();
    bool isUnknownOrInvalidOrVoid();
    virtual bool isLiteral();
    virtual void copyFrom(TypeSignature* otherType);
    virtual TypeSource getTypeTarget();
    virtual std::string toString() = 0;
    virtual TypeSource getTypeSource() = 0;
    virtual bool isEqualTo(TypeSignature* otherType) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_SIGNATURE_H
