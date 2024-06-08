//
// Created by Johny Georges on 2024-05-18.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H

#include <optional>
#include "../../../type-signature.h"
#include "../../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../invocable-type-signature.h"

class LambdaExpressionTypeSignature : public InvocableTypeSignature {
private:
    ParameterListTypeSignature* _parameterList;
    TypeSignature* _returnType;
public:
    LambdaExpressionTypeSignature();
    LambdaExpressionTypeSignature(ParameterListTypeSignature* parameterList, std::optional<TypeSignature*> returnType = {});
    ParameterListTypeSignature* getParameterList();
    std::vector<TypeSignature*>* getParameterTypes() override;
    TypeSignature* getReturnType() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H
