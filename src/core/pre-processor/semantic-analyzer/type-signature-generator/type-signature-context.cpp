//
// Created by Johny Georges on 2026-03-19.
//

#include "type-signature-context.h"

TypeSignatureContext::TypeSignatureContext() {
    _typeSignature = {};
    _typeSignatures = {};
}

TypeSignatureContext::TypeSignatureContext(std::optional<TypeSignature*> typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignatureContext::TypeSignatureContext(std::optional<std::vector<TypeSignature*>*> typeSignatures) {
    _typeSignatures = typeSignatures;
}

std::optional<TypeSignature*> TypeSignatureContext::getTypeSignature() {
    return _typeSignature;
}

std::optional<std::vector<TypeSignature*>*> TypeSignatureContext::getTypeSignatures() {
    return _typeSignatures;
}