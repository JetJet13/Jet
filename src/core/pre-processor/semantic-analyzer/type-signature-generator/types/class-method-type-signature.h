//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H
#define JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H

#include "type-signature.h"
#include "type.h"
#include "../../../../lexeme/lexeme.h"
#include "parameter-list-type-signature.h"
#include "access-modifier-type-signature.h"

class ClassMethodTypeSignature : public TypeSignature {
private:
    std::string _name;
    AccessModifierTypeSignature* _accessModifier;
    bool _isStatic;
    ParameterListTypeSignature* _parameterList;
    std::optional<TypeSignature*> _returnType;
public:
    ClassMethodTypeSignature(std::string name, AccessModifierTypeSignature* accessModifier, ParameterListTypeSignature* parameterList, bool isStatic, std::optional<TypeSignature*> returnType = {});
    std::string getName();
    bool isStatic();
    AccessModifierTypeSignature* getAccessModifier();
    ParameterListTypeSignature* getParameters();
    std::optional<TypeSignature*> getReturnType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H
