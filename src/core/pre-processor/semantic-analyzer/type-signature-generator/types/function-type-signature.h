//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_FUNCTION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_TYPE_SIGNATURE_H

#include <vector>
#include "type-signature.h"
#include "parameter-list-type-signature.h"

class FunctionTypeSignature : public TypeSignature {
private:
    std::string _name;
    ParameterListTypeSignature* _parameterList;
    TypeSignature* _returnType;
public:
    FunctionTypeSignature(std::string name, ParameterListTypeSignature* parameterList, TypeSignature* returnType);
    std::string getName();
    ParameterListTypeSignature* getParameterList();
    TypeSignature* getReturnType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_H
