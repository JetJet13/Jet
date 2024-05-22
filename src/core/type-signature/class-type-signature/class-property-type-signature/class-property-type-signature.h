//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_H
#define JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../../literal-type-signature/types/literal-type.h"
#include "../../../lexeme/lexeme.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../access-modifier-type-signature/access-modifier-type-signature.h"

class ClassPropertyTypeSignature : public TypeSignature {
private:
    AccessModifierTypeSignature* _accessModifier;
    bool _isStatic;
    bool _isConst;
    TypeSignature* _type;
public:
    ClassPropertyTypeSignature();
    ClassPropertyTypeSignature(AccessModifierTypeSignature* accessModifier, TypeSignature* type, bool isStatic, bool isConst);
    bool isStatic();
    bool isConst();
    AccessModifierTypeSignature* getAccessModifier();
    TypeSignature* getType();
    void setType(TypeSignature* typeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_H
