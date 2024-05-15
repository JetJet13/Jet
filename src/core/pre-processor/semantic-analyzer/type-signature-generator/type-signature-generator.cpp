//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"

TypeSignatureGenerator::TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider) {
    _typeSignatureStrategyProvider = typeSignatureStrategyProvider;
}

TypeSignature*  TypeSignatureGenerator::generateTypeSignatureForDeclaration(ASTDeclarationNode* node) {
    return _typeSignatureStrategyProvider->getTypeSignatureForDeclaration(node);
}