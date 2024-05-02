//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_FUNCTION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_TYPE_SIGNATURE_H

#include <vector>
#include "type-signature.h"

class FunctionTypeSignature : public TypeSignature {
private:
    std::vector<TypeSignature*>* _parameterTypes;
    TypeSignature* _returnType;
public:
    FunctionTypeSignature(std::vector<TypeSignature*>* parameterTypes, TypeSignature* returnType);
    std::vector<TypeSignature*>* getParameterTypes();
    TypeSignature* getReturnType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_H
