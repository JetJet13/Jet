//
// Created by Johny Georges on 2025-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_H

#include <optional>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../invocable-type-signature.h"
#include "../../struct-type-signature/struct-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"

class LambdaTypeSignature : public InvocableTypeSignature {
private:
    std::vector<TypeSignature*> _parameterTypes;
    TypeSignature* _returnType;
public:
    LambdaTypeSignature();
    LambdaTypeSignature(std::vector<TypeSignature*> parameterTypes, std::optional<TypeSignature*> returnType = {});
    int numParameters();
    std::vector<TypeSignature*>* getParameterTypes() override;
    TypeSignature* getReturnType() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSignature* getTargetTypeSignature() override;
    TypeSignature* convertToVariableTypeSignature() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_H
