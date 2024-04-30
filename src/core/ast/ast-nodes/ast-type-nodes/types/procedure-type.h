//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_PROCEDURE_TYPE_H
#define JETLANG_PROCEDURE_TYPE_H

#include <vector>
#include "base-type.h"

class ProcedureType : public BaseType {
private:
    std::vector<BaseType*>* _parameterTypes;
public:
    ProcedureType(std::vector<BaseType*>* parameterTypes);
    std::vector<BaseType*>* getParameterTypes();
    TypeSource getTypeSource() override;
    bool isEqualTo(BaseType *otherType) override;
};

#endif //JETLANG_PROCEDURE_TYPE_H
