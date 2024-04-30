//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TUPLE_TYPE_H
#define JETLANG_TUPLE_TYPE_H

#include <vector>
#include "base-type.h"

class TupleType : public BaseType {
private:
    std::vector<BaseType*>* _elementTypes;
public:
    TupleType(std::vector<BaseType*>* elementTypes);
    std::vector<BaseType*>* getElementTypes();
    TypeSource getTypeSource() override;
    bool isEqualTo(BaseType *otherType) override;
};

#endif //JETLANG_TUPLE_TYPE_H
