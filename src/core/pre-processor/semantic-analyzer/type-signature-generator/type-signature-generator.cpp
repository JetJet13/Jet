//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"
#include "../../../type-signature/module-type-signature/module-type-signature.h"

TypeSignatureGenerator::TypeSignatureGenerator() {
    _typeSignatureStrategyProvider = TypeSignatureStrategyProvider();
}

void TypeSignatureGenerator::assignInitialTypeSignatureFor(ASTDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope) {
    _typeSignatureStrategyProvider.assignInitialTypeSignatureFor(node, context, scope);
}

void TypeSignatureGenerator::assignPostInitialTypeSignatureFor(ASTDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope) {
    _typeSignatureStrategyProvider.assignPostInitialTypeSignatureFor(node, context, scope);
}

void  TypeSignatureGenerator::assignTypeSignatureFor(ASTNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope) {
    _typeSignatureStrategyProvider.assignTypeSignatureFor(node, context, scope);
}