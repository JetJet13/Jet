//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"
#include "../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"

class ClassTypeSignatureStrategy {
private:
    ClassConstructorTypeSignature* generateConstructorTypeSignature(ASTClassConstructorDeclarationNode* node);
    ClassPropertyTypeSignature* generatePropertyTypeSignature(ASTClassPropertyDeclarationNode* node);
    ClassMethodTypeSignature* generateMethodTypeSignature(ASTClassMethodDeclarationNode* node);
public:
    TypeSignature* create(ASTClassDeclarationNode* node);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H
