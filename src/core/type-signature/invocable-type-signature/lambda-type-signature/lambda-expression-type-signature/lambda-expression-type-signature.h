//
// Created by Johny Georges on 2024-05-18.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H

#include <optional>
#include "../../../type-signature.h"
#include "../../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../invocable-type-signature.h"
#include "../../../struct-type-signature/struct-type-signature.h"

class LambdaExpressionTypeSignature : public InvocableTypeSignature {
private:
    std::shared_ptr<ParameterListTypeSignature> _parameterList;
    std::shared_ptr<ParameterListItemTypeSignature> _scopeParameter;
    std::shared_ptr<TypeSignature> _returnType;
public:
    LambdaExpressionTypeSignature();
    LambdaExpressionTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList, std::shared_ptr<ParameterListItemTypeSignature> scopeParameter, std::optional<std::shared_ptr<TypeSignature>> returnType = {});
    std::shared_ptr<ParameterListItemTypeSignature> getScopeParameter();
    bool isScopeParameterNecessary();
    std::shared_ptr<ParameterListTypeSignature> getParameterList();
    bool hasScopeArgument() override;
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H
