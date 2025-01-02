//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../../struct-type-signature/struct-type-signature.h"
#include "../../pointer-type-signature/pointer-type-signature.h"

class ParameterListItemTypeSignature : public TypeSignature {
private:
    std::string _name;
    TypeSignature* _type;
public:
    static ParameterListItemTypeSignature* createScopeParameter(std::optional<StructTypeSignature*> scopeTypeSignature = {});
    static ParameterListItemTypeSignature* createClassScopeParameter(std::optional<PointerTypeSignature*> scopeTypeSignature = {});
    ParameterListItemTypeSignature(std::string name, TypeSignature* type);
    std::string getName();
    TypeSignature* getTypeSignature();
    void setType(TypeSignature* typeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_H
