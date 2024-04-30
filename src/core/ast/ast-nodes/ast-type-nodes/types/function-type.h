//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_FUNCTION_TYPE_H
#define JETLANG_FUNCTION_TYPE_H

#include <vector>
#include "base-type.h"

class FunctionType : public BaseType {
private:
    std::vector<BaseType*>* _parameterTypes;
    BaseType* _returnType;
public:
    FunctionType(std::vector<BaseType*>* parameterTypes, BaseType* returnType);
    std::vector<BaseType*>* getParameterTypes();
    BaseType* getReturnType();
    TypeSource getTypeSource() override;
    bool isEqualTo(BaseType *otherType) override;
};

#endif //JETLANG_FUNCTION_TYPE_H
