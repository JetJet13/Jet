//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_H
#define JETLANG_TYPE_SIGNATURE_H

#include <string>
#include "type.h"
#include "type-source.h"

class TypeSignature {
public:
    virtual std::string toString() = 0;
    virtual TypeSource getTypeSource() = 0;
    virtual bool isEqualTo(TypeSignature* otherType) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_SIGNATURE_H
