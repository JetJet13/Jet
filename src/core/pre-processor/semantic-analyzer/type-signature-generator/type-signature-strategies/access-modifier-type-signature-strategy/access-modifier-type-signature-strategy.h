//
// Created by Johny Georges on 2024-05-13.
//

#ifndef JETLANG_ACCESS_MODIFIER_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ACCESS_MODIFIER_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../../../../../ast/ast-nodes/ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "../../../../../type-signature/access-modifier-type-signature/access-modifier-type-signature.h"


class AccessModifierTypeSignatureStrategy {
public:
    void assign(ASTAccessModifierNode* accessModifierNode);
};

#endif //JETLANG_ACCESS_MODIFIER_TYPE_SIGNATURE_STRATEGY_H
