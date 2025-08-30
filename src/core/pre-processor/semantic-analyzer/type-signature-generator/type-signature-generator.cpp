//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"
#include "../../../type-signature/module-type-signature/module-type-signature.h"

TypeSignatureGenerator::TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider) {
    _typeSignatureStrategyProvider = typeSignatureStrategyProvider;
}

void TypeSignatureGenerator::assignInitialTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignInitialTypeSignatureFor(node, scope);
}

void TypeSignatureGenerator::assignPartialTypeSignatureForTypeDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignPartialTypeSignatureFor(node, scope);
}

void  TypeSignatureGenerator::assignTypeSignatureFor(ASTNode* node, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignTypeSignatureFor(node, scope);
}