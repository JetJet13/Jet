//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H
#define JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../../literal-type-signature/types/literal-type.h"
#include "../../../lexeme/lexeme.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../access-modifier-type-signature/access-modifier-type-signature.h"

class ClassMethodTypeSignature : public TypeSignature {
private:
    AccessModifierTypeSignature* _accessModifier;
    bool _isStatic;
    ParameterListTypeSignature* _parameterList;
    std::optional<TypeSignature*> _returnType;
public:
    ClassMethodTypeSignature(AccessModifierTypeSignature* accessModifier, ParameterListTypeSignature* parameterList, bool isStatic, std::optional<TypeSignature*> returnType = {});
    bool isStatic();
    AccessModifierTypeSignature* getAccessModifier();
    ParameterListTypeSignature* getParameters();
    std::optional<TypeSignature*> getReturnType();
    void setReturnType(TypeSignature* returnType);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H
