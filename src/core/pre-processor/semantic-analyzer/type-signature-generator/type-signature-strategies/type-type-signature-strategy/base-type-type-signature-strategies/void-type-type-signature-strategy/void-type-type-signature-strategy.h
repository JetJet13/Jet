//
// Created by Johny Georges on 2025-07-12.
//

#ifndef JETLANG_VOID_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_VOID_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../type-signature-strategy-provider.h"
#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-void-type-node.h"

class VoidTypeTypeSignatureStrategy {
public:
    void assign(ASTVoidTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_VOID_TYPE_TYPE_SIGNATURE_STRATEGY_H
