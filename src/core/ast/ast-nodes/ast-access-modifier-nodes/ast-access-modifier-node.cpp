//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-access-modifier-node.h"

void ASTAccessModifierNode::setTypeSignature(AccessModifierTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

AccessModifierTypeSignature* ASTAccessModifierNode::getTypeSignature() {
    return _typeSignature;
}