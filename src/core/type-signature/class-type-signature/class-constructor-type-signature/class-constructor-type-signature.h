//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
#define JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"

class ClassConstructorTypeSignature : public TypeSignature {
private:
    std::string _name;
    ParameterListTypeSignature* _parameterList;
public:
    ClassConstructorTypeSignature(std::string name, ParameterListTypeSignature* parameterList);
    std::string getName();
    ParameterListTypeSignature* getParameterList();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
