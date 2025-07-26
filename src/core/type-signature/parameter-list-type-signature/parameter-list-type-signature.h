//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "parameter-list-item-type-signature/parameter-list-item-type-signature.h"


class ParameterListTypeSignature : public TypeSignature {
private:
    std::vector<ParameterListItemTypeSignature*> _parameters;
    std::vector<TypeSignature*> _parameterTypes;
    bool _isVariableLength = false;
    unsigned long _variableLengthStartIndex = -1;
public:
    ParameterListTypeSignature();
    ParameterListTypeSignature(std::vector<ParameterListItemTypeSignature*> parameters);
    std::vector<ParameterListItemTypeSignature*>* getParameters();
    std::vector<TypeSignature*>* getParameterTypes();
    unsigned long numParameters();
    void markAsVariableLength(unsigned long startIndex);
    bool isVariableLength();
    unsigned long getVariableLengthStartIndex();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
