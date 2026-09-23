//
// Created by Johny Georges on 2024-06-08.
//

#ifndef JETLANG_INVOCABLE_TYPE_SIGNATURE_H
#define JETLANG_INVOCABLE_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../argument-list-type-signature/argument-list-type-signature.h"

class InvocableTypeSignature : public TypeSignature {
public:
    bool isInvocable() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    bool isArgumentVarArg(int argumentIndex);
    virtual bool hasScopeArgument();
    virtual bool hasVariableLengthParameters();
    virtual uint64_t getVariableLengthParametersStartIndex();
    virtual std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() = 0;
    virtual bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) = 0;
    virtual std::shared_ptr<TypeSignature> getReturnType() = 0;
};

#endif //JETLANG_INVOCABLE_TYPE_SIGNATURE_H
