//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_BASE_TYPE_H
#define JETLANG_BASE_TYPE_H

#include "type.h"
#include "type-source.h"

class BaseType {
public:
    virtual TypeSource getTypeSource() = 0;
    virtual bool isEqualTo(BaseType* otherType) = 0;
};

#endif //JETLANG_BASE_TYPE_H
