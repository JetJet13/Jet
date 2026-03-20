//
// Created by Johny Georges on 2026-03-19.
//

#ifndef JETLANG_TYPE_SIGNATURE_CONTEXT_H
#define JETLANG_TYPE_SIGNATURE_CONTEXT_H

#include "../../../type-signature/type-signature.h"

class TypeSignatureContext {
private:
    std::optional<TypeSignature*> _typeSignature;
    std::optional<std::vector<TypeSignature*>*> _typeSignatures;
public:
    TypeSignatureContext();
    TypeSignatureContext(std::optional<TypeSignature*> typeSignature);
    TypeSignatureContext(std::optional<std::vector<TypeSignature*>*> typeSignatures);
    std::optional<TypeSignature*> getTypeSignature();
    std::optional<std::vector<TypeSignature*>*> getTypeSignatures();
};

#endif //JETLANG_TYPE_SIGNATURE_CONTEXT_H
