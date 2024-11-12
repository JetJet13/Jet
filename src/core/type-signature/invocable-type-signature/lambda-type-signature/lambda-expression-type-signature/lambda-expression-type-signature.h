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
    StructTypeSignature* _scopeParameter;
    TypeSignature* _returnType;
public:
    LambdaExpressionTypeSignature();
    LambdaExpressionTypeSignature(ParameterListTypeSignature* parameterList, StructTypeSignature* scopeParameter, std::optional<TypeSignature*> returnType = {});
    StructTypeSignature* getScopeParameter();
    ParameterListTypeSignature* getParameterList();
    std::vector<TypeSignature*>* getParameterTypes() override;
    TypeSignature* getReturnType() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_H
