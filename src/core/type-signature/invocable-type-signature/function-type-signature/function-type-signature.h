//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_FUNCTION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_TYPE_SIGNATURE_H

#include <string>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../invocable-type-signature.h"

class FunctionTypeSignature : public InvocableTypeSignature {
private:
    std::shared_ptr<ParameterListTypeSignature> _parameterList;
    std::shared_ptr<TypeSignature> _returnType;
public:
    FunctionTypeSignature();
    FunctionTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList, std::shared_ptr<TypeSignature> returnType);
    std::shared_ptr<ParameterListTypeSignature> getParameterList();
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    std::shared_ptr<TypeSignature> getTargetTypeSignature() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void copyFrom(std::shared_ptr<TypeSignature> otherType) override;
    bool hasVariableLengthParameters() override;
    unsigned long getVariableLengthParametersStartIndex() override;
    void print() override;
};

#endif //JETLANG_FUNCTION_TYPE_SIGNATURE_H
