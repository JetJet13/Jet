//
// Created by Johny Georges on 2026-03-19.
//

#include "type-signature-context.h"

TypeSignatureContext::TypeSignatureContext() {
    _typeSignature = {};
    _typeSignatures = {};
}

TypeSignatureContext::TypeSignatureContext(std::optional<std::shared_ptr<TypeSignature>> typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignatureContext::TypeSignatureContext(std::optional<std::vector<std::shared_ptr<TypeSignature>>*> typeSignatures) {
    _typeSignatures = typeSignatures;
}

std::optional<std::shared_ptr<TypeSignature>> TypeSignatureContext::getTypeSignature() {
    return _typeSignature;
}

std::optional<std::vector<std::shared_ptr<TypeSignature>>*> TypeSignatureContext::getTypeSignatures() {
    return _typeSignatures;
}