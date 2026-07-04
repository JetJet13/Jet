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
    std::shared_ptr<InvocableTypeSignature> _invocableTypeSignature;
public:
    FunctionInvocationTypeSignature();
    FunctionInvocationTypeSignature(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature);
    std::shared_ptr<InvocableTypeSignature> getFunctionType();
    std::shared_ptr<TypeSignature> getReturnType();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    std::shared_ptr<TypeSignature> getTargetTypeSignature() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
