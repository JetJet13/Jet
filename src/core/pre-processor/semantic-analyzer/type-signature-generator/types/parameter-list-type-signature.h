//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H

#include <vector>
#include "type-signature.h"
#include "type.h"
#include "parameter-item-type-signature.h"


class ParameterListTypeSignature : public TypeSignature {
private:
    std::vector<ParameterItemTypeSignature*> _parameters;
public:
    ParameterListTypeSignature(std::vector<ParameterItemTypeSignature*> parameters);
    std::vector<ParameterItemTypeSignature*>* getParameters();
    unsigned long numParameters();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
