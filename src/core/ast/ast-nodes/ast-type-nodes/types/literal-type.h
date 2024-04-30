//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_LITERAL_TYPE_H
#define JETLANG_LITERAL_TYPE_H

#include "base-type.h"
#include "type.h"

class LiteralType : public BaseType {
private:
    Type _coreType;
public:
    LiteralType(Type type);
    Type getType();
    TypeSource getTypeSource() override;
    bool isEqualTo(BaseType *otherType) override;
};

#endif //JETLANG_LITERAL_TYPE_H
