//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_PROCEDURE_TYPE_SIGNATURE_H
#define JETLANG_PROCEDURE_TYPE_SIGNATURE_H

#include <vector>
#include "type-signature.h"
#include "parameter-list-type-signature.h"

class ProcedureTypeSignature : public TypeSignature {
private:
    std::string _name;
    ParameterListTypeSignature* _parameterList;
public:
    ProcedureTypeSignature(std::string name, ParameterListTypeSignature* parameterList);
    std::string getName();
    ParameterListTypeSignature* getParameterList();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_PROCEDURE_TYPE_SIGNATURE_H
