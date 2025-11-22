//
// Created by Johny Georges on 2025-11-21.
//

#ifndef JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class LambdaScopeTypeSignature : public TypeSignature {
private:
    std::vector<std::string> _capturedVariableIds;
public:
    LambdaScopeTypeSignature();
    LambdaScopeTypeSignature(std::vector<std::string>* capturedVariables);
    std::vector<std::string>* getCapturedVariableIds();
    bool isEmpty();
    void addCapturedVariableId(std::string capturedVariableId);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_H
