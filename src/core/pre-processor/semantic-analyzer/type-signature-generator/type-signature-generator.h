//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_GENERATOR_H
#define JETLANG_TYPE_SIGNATURE_GENERATOR_H

#include "type-signature-strategies/type-signature-strategy-provider.h"

class TypeSignatureGenerator {
private:
    TypeSignatureStrategyProvider _typeSignatureStrategyProvider;
public:
    TypeSignatureGenerator();
    void assignInitialTypeSignatureFor(ASTDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope);
    void assignPostInitialTypeSignatureFor(ASTDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope);
    void assignTypeSignatureFor(ASTNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope);
};
#endif //JETLANG_TYPE_SIGNATURE_GENERATOR_H
