//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-base-node.h"


void ASTTypeBaseNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTTypeBaseNode::getTypeSignature() {
    return _typeSignature;
}