//
// Created by Johny Georges on 2024-05-13.
//

#include "access-modifier-type-signature-strategy.h"

void AccessModifierTypeSignatureStrategy::assign(ASTAccessModifierNode* accessModifierNode) {
    switch (accessModifierNode->getNodeType()) {
        case AST_PUBLIC_NODE:
            accessModifierNode->setTypeSignature(new AccessModifierTypeSignature(PUBLIC_ACCESS_MODIFIER_TYPE));
            break;
        case AST_PROTECTED_NODE:
            accessModifierNode->setTypeSignature(new AccessModifierTypeSignature(PROTECTED_ACCESS_MODIFIER_TYPE));
            break;
        case AST_PRIVATE_NODE:
            accessModifierNode->setTypeSignature(new AccessModifierTypeSignature(PRIVATE_ACCESS_MODIFIER_TYPE));
            break;
        default:
            throw std::invalid_argument("unknown access modifier type");
    }
}