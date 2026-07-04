//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
#define JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"
#include "../../invocable-type-signature/invocable-type-signature.h"

class ClassConstructorTypeSignature : public InvocableTypeSignature {
private:
    std::shared_ptr<ParameterListTypeSignature> _parameterList;
    std::shared_ptr<VoidTypeSignature> _returnTypeSignature = std::make_shared<VoidTypeSignature>();
public:
    explicit ClassConstructorTypeSignature();
    explicit ClassConstructorTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList);
    std::shared_ptr<ParameterListTypeSignature> getParameterList();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool matchArguments(std::vector<std::shared_ptr<TypeSignature>>* argumentTypeSignatures);
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
