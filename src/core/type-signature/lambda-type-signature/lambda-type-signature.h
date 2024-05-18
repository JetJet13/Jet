//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_H

#include <string>
#include <optional>
#include "../type-signature.h"
#include "../parameter-list-type-signature/parameter-list-type-signature.h"

class LambdaTypeSignature : public TypeSignature {
private:
    std::vector<TypeSignature*>* _parameterTypes;
    std::optional<TypeSignature*> _returnType;
public:
    LambdaTypeSignature(std::vector<TypeSignature*>* parameterTypes, std::optional<TypeSignature*> returnType = {});
    LambdaTypeSignature(std::vector<TypeSignature*> parameterTypes, std::optional<TypeSignature*> returnType = {});
    std::vector<TypeSignature*>* getParameterTypes();
    std::optional<TypeSignature*> getReturnType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_H
