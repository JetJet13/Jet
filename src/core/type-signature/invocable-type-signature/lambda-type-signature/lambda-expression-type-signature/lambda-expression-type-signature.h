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
    ParameterListTypeSignature* _parameterList;
    ParameterListItemTypeSignature* _scopeParameter;
    TypeSignature* _returnType;
public:
    LambdaExpressionTypeSignature();
    LambdaExpressionTypeSignature(ParameterListTypeSignature* parameterList, ParameterListItemTypeSignature* scopeParameter, std::optional<TypeSignature*> returnType = {});
    ParameterListItemTypeSignature* getScopeParameter();
    bool isScopeParameterNecessary();
    ParameterListTypeSignature* getParameterList();
    bool hasScopeArgument() override;
    std::vector<TypeSignature*>* getParameterTypes() override;
    bool doArgumentsMatchParameters(ArgumentListTypeSignature* argumentListTypeSignature) override;
    TypeSignature* getReturnType() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H
