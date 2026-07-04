//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_ACCESS_MODIFIER_TYPE_SIGNATURE_H
#define JETLANG_ACCESS_MODIFIER_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "access-modifier-type.h"

class AccessModifierTypeSignature : public TypeSignature {
private:
    AccessModifierType _accessModifier;
public:
    AccessModifierTypeSignature(AccessModifierType accessModifier = PRIVATE_ACCESS_MODIFIER_TYPE);
    bool isPublic();
    bool isProtected();
    bool isPrivate();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;

};

#endif //JETLANG_ACCESS_MODIFIER_TYPE_SIGNATURE_H
