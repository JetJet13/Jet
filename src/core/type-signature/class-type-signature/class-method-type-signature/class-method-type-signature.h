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
#include "../../invocable-type-signature/invocable-type-signature.h"

class ClassMethodTypeSignature : public InvocableTypeSignature {
private:
    std::shared_ptr<AccessModifierTypeSignature> _accessModifier;
    bool _isStatic;
    std::shared_ptr<ParameterListTypeSignature> _parameterList;
    std::shared_ptr<TypeSignature> _returnType;
public:
    ClassMethodTypeSignature();
    ClassMethodTypeSignature(std::shared_ptr<AccessModifierTypeSignature> accessModifier, std::shared_ptr<ParameterListTypeSignature> parameterList, bool isStatic, std::optional<std::shared_ptr<TypeSignature>> returnType = {});
    bool isStatic();
    std::shared_ptr<AccessModifierTypeSignature> getAccessModifier();
    std::shared_ptr<ParameterListTypeSignature> getParameters();
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    void setReturnType(std::shared_ptr<TypeSignature> returnType);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_METHOD_TYPE_SIGNATURE_H
