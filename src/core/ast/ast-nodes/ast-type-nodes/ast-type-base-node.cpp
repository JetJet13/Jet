//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-type-base-node.h"


void ASTTypeBaseNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTTypeBaseNode::getTypeSignature() {
    return _typeSignature;
}