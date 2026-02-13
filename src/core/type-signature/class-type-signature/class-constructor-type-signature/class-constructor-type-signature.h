//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
#define JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"
#include "../../invocable-type-signature/invocable-type-signature.h"

class ClassConstructorTypeSignature : public InvocableTypeSignature {
private:
    ParameterListTypeSignature* _parameterList;
    VoidTypeSignature* _returnTypeSignature = new VoidTypeSignature();
public:
    explicit ClassConstructorTypeSignature();
    explicit ClassConstructorTypeSignature(ParameterListTypeSignature* parameterList);
    ParameterListTypeSignature* getParameterList();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool matchArguments(std::vector<TypeSignature*>* argumentTypeSignatures);
    std::vector<TypeSignature*>* getParameterTypes() override;
    bool doArgumentsMatchParameters(ArgumentListTypeSignature* argumentListTypeSignature) override;
    TypeSignature* getReturnType() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
