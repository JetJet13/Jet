//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_ITEM_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_ITEM_TYPE_SIGNATURE_H

#include <vector>
#include "type-signature.h"

class ParameterItemTypeSignature : public TypeSignature {
private:
    std::string _name;
    TypeSignature* _type;
public:
    ParameterItemTypeSignature(std::string name, TypeSignature* type);
    std::string getName();
    TypeSignature* getType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_PARAMETER_ITEM_TYPE_SIGNATURE_H
