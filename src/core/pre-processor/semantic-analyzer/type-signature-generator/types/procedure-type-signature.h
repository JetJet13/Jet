//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_PROCEDURE_TYPE_SIGNATURE_H
#define JETLANG_PROCEDURE_TYPE_SIGNATURE_H

#include <vector>
#include "type-signature.h"

class ProcedureTypeSignature : public TypeSignature {
private:
    std::vector<TypeSignature*>* _parameterTypes;
public:
    ProcedureTypeSignature(std::vector<TypeSignature*>* parameterTypes);
    std::vector<TypeSignature*>* getParameterTypes();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_PROCEDURE_TYPE_SIGNATURE_H
