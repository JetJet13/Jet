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
    std::shared_ptr<AccessModifierTypeSignature> _accessModifier;
    bool _isStatic;
    bool _isConst;
    std::shared_ptr<TypeSignature> _type;
public:
    ClassPropertyTypeSignature();
    ClassPropertyTypeSignature(std::shared_ptr<AccessModifierTypeSignature> accessModifier, std::shared_ptr<TypeSignature> type, bool isStatic, bool isConst);
    bool isStatic();
    bool isConst();
    std::shared_ptr<AccessModifierTypeSignature> getAccessModifier();
    std::shared_ptr<TypeSignature> getType();
    void setType(std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    void print() override;
};

#endif //JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_H
