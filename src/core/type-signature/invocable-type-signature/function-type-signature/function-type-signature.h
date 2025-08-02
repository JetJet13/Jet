//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_FUNCTION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_TYPE_SIGNATURE_H

#include <string>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../invocable-type-signature.h"

class FunctionTypeSignature : public InvocableTypeSignature {
private:
    ParameterListTypeSignature* _parameterList;
    TypeSignature* _returnType;
public:
    FunctionTypeSignature();
    FunctionTypeSignature(ParameterListTypeSignature* parameterList, TypeSignature* returnType);
    ParameterListTypeSignature* getParameterList();
    std::vector<TypeSignature*>* getParameterTypes() override;
    bool doArgumentsMatchParameters(ArgumentListTypeSignature* argumentListTypeSignature) override;
    TypeSignature* getReturnType() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSignature* getTargetTypeSignature() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void copyFrom(TypeSignature* otherType) override;
    bool hasVariableLengthParameters() override;
    unsigned long getVariableLengthParametersStartIndex() override;
    void print() override;
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_H
