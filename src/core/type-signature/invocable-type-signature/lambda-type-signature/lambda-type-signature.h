//
// Created by Johny Georges on 2025-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_H

#include <optional>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../invocable-type-signature.h"
#include "../../struct-type-signature/struct-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"

class LambdaTypeSignature : public InvocableTypeSignature {
private:
    std::vector<std::shared_ptr<TypeSignature>> _parameterTypes;
    std::shared_ptr<TypeSignature> _returnType;
public:
    LambdaTypeSignature();
    LambdaTypeSignature(std::vector<std::shared_ptr<TypeSignature>> parameterTypes, std::optional<std::shared_ptr<TypeSignature>> returnType = {});
    int numParameters();
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool hasScopeArgument() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_H
