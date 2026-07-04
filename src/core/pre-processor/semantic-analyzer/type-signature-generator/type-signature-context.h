//
// Created by Johny Georges on 2026-03-19.
//

#ifndef JETLANG_TYPE_SIGNATURE_CONTEXT_H
#define JETLANG_TYPE_SIGNATURE_CONTEXT_H

#include "../../../type-signature/type-signature.h"

class TypeSignatureContext {
private:
    std::optional<std::shared_ptr<TypeSignature>> _typeSignature;
    std::optional<std::vector<std::shared_ptr<TypeSignature>>*> _typeSignatures;
public:
    TypeSignatureContext();
    TypeSignatureContext(std::optional<std::shared_ptr<TypeSignature>> typeSignature);
    TypeSignatureContext(std::optional<std::vector<std::shared_ptr<TypeSignature>>*> typeSignatures);
    std::optional<std::shared_ptr<TypeSignature>> getTypeSignature();
    std::optional<std::vector<std::shared_ptr<TypeSignature>>*> getTypeSignatures();
};

#endif //JETLANG_TYPE_SIGNATURE_CONTEXT_H
