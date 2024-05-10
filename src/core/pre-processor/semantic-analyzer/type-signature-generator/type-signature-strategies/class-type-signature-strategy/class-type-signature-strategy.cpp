//
// Created by Johny Georges on 2024-05-04.
//

#include "class-type-signature-strategy.h"
#include "../../../../../type-signature/class-type-signature/class-type-signature.h"

TypeSignature* ClassTypeSignatureStrategy::create(ASTClassDeclarationNode* node) {
    auto classTypeSignature = new ClassTypeSignature(node->getId());
    return classTypeSignature;
}

ClassConstructorTypeSignature* ClassTypeSignatureStrategy::generateConstructorTypeSignature(ASTClassConstructorDeclarationNode* node) {
}

ClassPropertyTypeSignature* ClassTypeSignatureStrategy::generatePropertyTypeSignature(ASTClassPropertyDeclarationNode* node) {}

ClassMethodTypeSignature* ClassTypeSignatureStrategy::generateMethodTypeSignature(ASTClassMethodDeclarationNode* node) {}