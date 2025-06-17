//
// Created by Johny Georges on 2024-06-08.
//

#ifndef JETLANG_FUNCTION_LAMBDA_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_LAMBDA_TYPE_SIGNATURE_H

#include <string>
#include "../../../type-signature.h"
#include "../../invocable-type-signature.h"

class FunctionLambdaTypeSignature : public InvocableTypeSignature {
private:
    std::vector<TypeSignature*>* _parameterTypes;
    TypeSignature* _returnType;
public:
    FunctionLambdaTypeSignature(std::vector<TypeSignature*>* parameterTypes, TypeSignature* returnType);
    FunctionLambdaTypeSignature(std::vector<TypeSignature*> parameterTypes, TypeSignature* returnType);
    FunctionLambdaTypeSignature(TypeSignature* returnType);
    std::vector<TypeSignature*>* getParameterTypes() override;
    TypeSignature* getReturnType() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSignature* getTargetTypeSignature() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_LAMBDA_TYPE_SIGNATURE_H
