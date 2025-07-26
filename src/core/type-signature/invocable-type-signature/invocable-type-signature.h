//
// Created by Johny Georges on 2024-06-08.
//

#ifndef JETLANG_INVOCABLE_TYPE_SIGNATURE_H
#define JETLANG_INVOCABLE_TYPE_SIGNATURE_H

#include "../type-signature.h"

class InvocableTypeSignature : public TypeSignature {
public:
    bool isInvocable() override;
    bool isEquivalentTo(TypeSignature* otherType) override;
    TypeSignature* convertToVariableTypeSignature() override;
    virtual bool hasVariableLengthParameters();
    virtual unsigned long getVariableLengthParametersStartIndex();
    virtual std::vector<TypeSignature*>* getParameterTypes() = 0;
    virtual TypeSignature* getReturnType() = 0;
};

#endif //JETLANG_INVOCABLE_TYPE_SIGNATURE_H
