//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_GENERATOR_H
#define JETLANG_TYPE_SIGNATURE_GENERATOR_H

#include "type-signature-strategies/type-signature-strategy-provider.h"

class TypeSignatureGenerator {
private:
    TypeSignatureStrategyProvider* _typeSignatureStrategyProvider;
public:
    explicit TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider);
    TypeSignature* generateInitialTypeSignatureForTypeDeclaration(ASTDeclarationNode* node);
    TypeSignature* generateTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope);
};
#endif //JETLANG_TYPE_SIGNATURE_GENERATOR_H
