//
// Created by Johny Georges on 2024-05-16.
//

#ifndef JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H

#include <string>
#include "../../../type-signature.h"
#include "../function-type-signature.h"
#include "../../invocable-type-signature.h"


class FunctionInvocationTypeSignature : public TypeSignature {
private:
    InvocableTypeSignature* _invocableTypeSignature;
public:
    FunctionInvocationTypeSignature();
    FunctionInvocationTypeSignature(InvocableTypeSignature* invocableTypeSignature);
    InvocableTypeSignature* getFunctionType();
    TypeSignature* getReturnType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    TypeSignature* getTargetTypeSignature() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
