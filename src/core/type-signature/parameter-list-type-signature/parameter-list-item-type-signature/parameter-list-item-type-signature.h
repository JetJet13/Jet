//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../../pointer-type-signature/pointer-type-signature.h"
#include "../../lambda-scope-type-signature/lambda-scope-type-signature.h"

class ParameterListItemTypeSignature : public TypeSignature {
private:
    std::string _name;
    std::shared_ptr<TypeSignature> _type;
public:
    static std::shared_ptr<ParameterListItemTypeSignature> createScopeParameter(std::optional<std::shared_ptr<LambdaScopeTypeSignature>> scopeTypeSignature = {});
    static std::shared_ptr<ParameterListItemTypeSignature> createClassScopeParameter(std::optional<std::shared_ptr<PointerTypeSignature>> scopeTypeSignature = {});
    ParameterListItemTypeSignature(std::string name, std::shared_ptr<TypeSignature> type);
    std::string getName();
    std::shared_ptr<TypeSignature> getTypeSignature();
    void setType(std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_PARAMETER_LIST_ITEM_TYPE_SIGNATURE_H
