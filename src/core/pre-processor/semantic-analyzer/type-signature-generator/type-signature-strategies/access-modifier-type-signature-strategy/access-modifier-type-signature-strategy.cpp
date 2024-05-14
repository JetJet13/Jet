//
// Created by Johny Georges on 2024-05-13.
//

#include "access-modifier-type-signature-strategy.h"
#include "../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../type-signature/access-modifier-type-signature/access-modifier-type-signature.h"

AccessModifierTypeSignature* AccessModifierTypeSignatureStrategy::create(ASTAccessModifierNode* accessModifierNode) {
    switch (accessModifierNode->getNodeType()) {
        case AST_PUBLIC_NODE:
            return new AccessModifierTypeSignature(PUBLIC_ACCESS_MODIFIER_TYPE);
        case AST_PROTECTED_NODE:
            return new AccessModifierTypeSignature(PROTECTED_ACCESS_MODIFIER_TYPE);
        case AST_PRIVATE_NODE:
            return new AccessModifierTypeSignature(PRIVATE_ACCESS_MODIFIER_TYPE);
        default:
            throw std::invalid_argument("unknown access modifier type");
    }
}