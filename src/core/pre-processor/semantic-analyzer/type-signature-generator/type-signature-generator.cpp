//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"
#include "../../../type-signature/module-type-signature/module-type-signature.h"

TypeSignatureGenerator::TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider) {
    _typeSignatureStrategyProvider = typeSignatureStrategyProvider;
}

void TypeSignatureGenerator::assignInitialTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignInitialTypeSignatureFor(node, context, scope);
}

void TypeSignatureGenerator::assignPartialTypeSignatureForTypeDeclaration(ASTDeclarationNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignPartialTypeSignatureFor(node, context, scope);
}

void  TypeSignatureGenerator::assignTypeSignatureFor(ASTNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignTypeSignatureFor(node, context, scope);
}