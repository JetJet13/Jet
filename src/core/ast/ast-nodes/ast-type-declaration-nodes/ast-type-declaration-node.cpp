//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-type-declaration-node.h"

void ASTTypeDeclarationNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTTypeDeclarationNode::getTypeSignature() {
    return _typeSignature;
}