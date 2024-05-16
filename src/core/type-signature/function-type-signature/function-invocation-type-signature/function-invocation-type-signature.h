//
// Created by Johny Georges on 2024-05-16.
//

#ifndef JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H

#include <string>
#include "../../type-signature.h"
#include "../function-type-signature.h"


class FunctionInvocationTypeSignature : public TypeSignature {
private:
    FunctionTypeSignature* _functionTypeSignature;
public:
    FunctionInvocationTypeSignature(FunctionTypeSignature* functionTypeSignature);
    FunctionTypeSignature* getFunctionType();
    TypeSignature* getReturnType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
