//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_PROCEDURE_TYPE_SIGNATURE_H
#define JETLANG_PROCEDURE_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../invocable-type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"

class ProcedureTypeSignature : public InvocableTypeSignature {
private:
    ParameterListTypeSignature* _parameterList;
    VoidTypeSignature* _returnType = new VoidTypeSignature();
public:
    ProcedureTypeSignature();
    explicit ProcedureTypeSignature(ParameterListTypeSignature* parameterList);
    ParameterListTypeSignature* getParameterList();
    std::vector<TypeSignature*>* getParameterTypes() override;
    TypeSignature* getReturnType() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSignature* getTargetTypeSignature() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void copyFrom(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_PROCEDURE_TYPE_SIGNATURE_H
