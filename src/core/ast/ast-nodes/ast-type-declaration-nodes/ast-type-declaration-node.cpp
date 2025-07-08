//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-type-declaration-node.h"

void ASTTypeDeclarationNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTTypeDeclarationNode::getTypeSignature() {
    return _typeSignature;
}