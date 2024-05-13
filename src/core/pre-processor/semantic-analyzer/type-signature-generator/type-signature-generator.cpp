//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"

TypeSignatureGenerator::TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider) {
    _typeSignatureStrategyProvider = typeSignatureStrategyProvider;
}

TypeSignature*  TypeSignatureGenerator::generateTypeSignatureFor(ASTNode* node) {
    return _typeSignatureStrategyProvider->getTypeSignatureFor(node);
}