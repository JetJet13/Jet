//
// Created by Johny Georges on 2024-06-08.
//

#ifndef JETLANG_PROCEDURE_LAMBDA_TYPE_SIGNATURE_H
#define JETLANG_PROCEDURE_LAMBDA_TYPE_SIGNATURE_H

#include <string>
#include "../../../type-signature.h"
#include "../../invocable-type-signature.h"
#include "../../../void-type-signature/void-type-signature.h"

class ProcedureLambdaTypeSignature : public InvocableTypeSignature {
private:
    std::vector<TypeSignature*>* _parameterTypes;
    VoidTypeSignature* _returnType = new VoidTypeSignature();
public:
    ProcedureLambdaTypeSignature(std::vector<TypeSignature*>* parameterTypes);
    ProcedureLambdaTypeSignature(std::vector<TypeSignature*> parameterTypes);
    std::vector<TypeSignature*>* getParameterTypes() override;
    TypeSignature* getReturnType() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSignature* getTargetTypeSignature() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_PROCEDURE_LAMBDA_TYPE_SIGNATURE_H
