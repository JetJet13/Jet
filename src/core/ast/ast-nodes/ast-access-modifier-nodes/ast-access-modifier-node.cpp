//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-access-modifier-node.h"

void ASTAccessModifierNode::setTypeSignature(std::shared_ptr<AccessModifierTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<AccessModifierTypeSignature> ASTAccessModifierNode::getAccessModifierTypeSignature() {
    return std::dynamic_pointer_cast<AccessModifierTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTAccessModifierNode::getTypeSignature() {
    return _typeSignature;
}